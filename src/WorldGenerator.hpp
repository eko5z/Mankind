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
	std::vector<std::vector<int>> heightmap;
};

