#include "TerrainGenerator.hpp"
#include "Log.hpp"

#include <random>
#include <numeric>
#include <algorithm>
#include <cmath>

#include "Game.hpp"

TerrainGenerator::TerrainGenerator(Game& game, int seed):
	game(game),
	seed(seed),
	p(256)
{
	srand(seed);
	std::iota(std::begin(p), std::end(p), 0);
	std::default_random_engine engine(seed);
	std::shuffle(std::begin(p), std::end(p), engine);
	p.insert(std::end(p), std::begin(p), std::end(p));
}

double TerrainGenerator::fade(double t)
{
	return t * t * t * (t * (t * 6 - 15) + 10);
}

double TerrainGenerator::lerp(double t, double a, double b)
{
	return a + t * (b - a);
}

double TerrainGenerator::grad(int hash, double x, double y, double z)
{
	int h = hash & 15;
	// Convert lower 4 bits of hash into 12 gradient directions
	double u = h < 8 ? x : y,
	       v = h < 4 ? y : h == 12 || h == 14 ? x : z;
	return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

double TerrainGenerator::noise(double x, double y, double z)
{
	// Find the unit cube that contains the point
	int X = (int) floor(x) & 255;
	int Y = (int) floor(y) & 255;
	int Z = (int) floor(z) & 255;

	// Find relative x, y,z of point in cube
	x -= floor(x);
	y -= floor(y);
	z -= floor(z);

	// Compute fade curves for each of x, y, z
	double u = fade(x);
	double v = fade(y);
	double w = fade(z);

	// Hash coordinates of the 8 cube corners
	int A = p[X] + Y;
	int AA = p[A] + Z;
	int AB = p[A + 1] + Z;
	int B = p[X + 1] + Y;
	int BA = p[B] + Z;
	int BB = p[B + 1] + Z;

	// Add blended results from 8 corners of cube
	double res = lerp(w,
	                  lerp(v, lerp(u, grad(p[AA], x, y, z), grad(p[BA], x-1, y, z)),
	                       lerp(u, grad(p[AB], x, y-1, z), grad(p[BB], x-1, y-1, z))),
	                  lerp(v, lerp(u, grad(p[AA+1], x, y, z-1),grad(p[BA+1], x-1, y, z-1)),
	                       lerp(u, grad(p[AB+1], x, y-1, z-1),	grad(p[BB+1], x-1, y-1, z-1))));
	return (res + 1.0)/2.0;
}

int TerrainGenerator::HeightAt(int x, int z)
{
	int acc(0);
	float u = ((float)x / 100.);
	float v = ((float)z / 100.);
	u = u < 0 ? u * -1 : u;
	v = v < 0 ? v * -1 : v;
	for (int i(1); i < 5; ++i) {
		float n = noise(u, 0.5, v);
		acc += (n * 200) / i;
		v = u;
		u /= 2;
	}
	return acc;
}

void TerrainGenerator::GenerateChunk(Chunk& c)
{
	int baseX(c.GetX() * CHUNK_SIZE),
	    baseY(c.GetY() * CHUNK_SIZE),
	    baseZ(c.GetZ() * CHUNK_SIZE);
	for (int i(0); i < CHUNK_SIZE; ++i) {
		for (int j(0); j < CHUNK_SIZE; ++j) {
			int newHeight = HeightAt(baseX+i, baseZ+j);
			int in_chunk_height = std::min(newHeight - baseY, CHUNK_SIZE);
			bool column_is_terrain(in_chunk_height > 0 and in_chunk_height < CHUNK_SIZE); /* neither empty nor full*/
			if (in_chunk_height < 0) {
				in_chunk_height = 0;
			}
			for (int k(0); k < in_chunk_height; ++k) {
				int typeID = 1;
				if (k + baseY == newHeight - 1) {
					typeID = 2;
				}
				c.SetCube(i, k, j, Cube{typeID});
			}
			if (rand() % 10 == 1 and column_is_terrain) {
				game.CreateTree(glm::vec3(baseX+i, newHeight+3, baseZ+j));
			}
		}
	}
}

