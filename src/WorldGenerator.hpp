#pragma once

#include <vector>
#include <cstdlib>

#include "Chunk.hpp"

class WorldGenerator
{
public:
	WorldGenerator(int seed);
	void GenerateChunk(Chunk& c);
private:
	int seed;
	int HeightAt(int x, int z);
	std::vector<std::vector<int>> heightmap;
};

