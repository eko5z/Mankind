#include "WorldGenerator.hpp"
#include "Log.hpp"

WorldGenerator::WorldGenerator(int seed):
	seed(seed),
	heightmap(64, std::vector<int>(64))
{
	srand(seed);
	for (int i(0); i < 64; ++i) {
		for (int j(0); j < 64; ++j) {
			heightmap[i][j] = rand() % 2;
		}
	}
}

int WorldGenerator::HeightAt(int x, int z)
{
	int ax = x + 512, az = z + 512;
	if (ax < 0 or ax >= 1024 or az < 0 or az >= 1024) {
		return 0;
	}

	int h = 0;
	for (int i(1); i < 10; ++i) {
		h += heightmap[ax%i][az%i] * (i / 3);
	}
	return h;
}

void WorldGenerator::GenerateChunk(Chunk& c)
{
	LOG("Generating chunk");
	int baseX(c.GetX() * CHUNK_SIZE),
	    baseY(c.GetY() * CHUNK_SIZE),
	    baseZ(c.GetZ() * CHUNK_SIZE);
	for (int i(0); i < CHUNK_SIZE; ++i) {
		for (int j(0); j < CHUNK_SIZE; ++j) {
			int newHeight = HeightAt(baseX+i, baseZ+j);
			if (rand() % 100 == 0)
					std::cerr<<"Height("<<baseX+i << ", " << baseZ+j <<") = "<<newHeight<<std::endl;
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

