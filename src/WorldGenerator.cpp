#include "WorldGenerator.hpp"
#include "Log.hpp"

WorldGenerator::WorldGenerator(int seed):
	seed(seed),
	heightmap(16, std::vector<int>(16))
{
	srand(seed);
	for (int i(0); i < 16; ++i) {
		for (int j(0); j < 16; ++j) {
			heightmap[i][j] = rand() % 2;
		}
	}
}

void WorldGenerator::GenerateChunk(Chunk& c)
{
	LOG("Generating chunk");
	int baseX(c.GetX() * CHUNK_SIZE),
	    baseY(c.GetY() * CHUNK_SIZE),
	    baseZ(c.GetZ() * CHUNK_SIZE);
	int baseHeight = heightmap[ c.GetX() + 8]     [ c.GetZ() + 8]      * 2
	                 + heightmap[(c.GetY() + 8) / 2][(c.GetZ() + 8) / 2] * 4
	                 + heightmap[(c.GetY() + 8) / 4][(c.GetZ() + 8) / 4] * 8;
	for (int i(0); i < CHUNK_SIZE; ++i) {
		for (int j(0); j < CHUNK_SIZE; ++j) {
			int newHeight = baseHeight + rand() % 2;
			int in_chunk_height = std::min(newHeight - baseY, 16);
			if (in_chunk_height < 0) {
				in_chunk_height = 0;
			}
			for (int k(0); k < in_chunk_height; ++k) {
				c.SetCube(i, k, j, Cube{1});
			}
		}
	}
}

