#pragma once

#include <vector>
#include <cstdlib>

#include "Chunk.hpp"

class Game;

class TerrainGenerator
{
public:
	TerrainGenerator(Game& game, int seed);
	void GenerateChunk(Chunk& c);
	int HeightAt(int x, int z);
private:
	Game& game;
	int seed;
	std::vector<int> p;
	double fade(double t);
	double lerp(double t, double a, double b);
	double grad(int hash, double x, double y, double z);
	double noise(double x, double y, double z);
};

