#pragma once

#include "Chunk.hpp"
#include <map>
#include <tuple>
#include <memory>

#define CHUNK_ID(x, y, z) ((x)<<20 + (y)<<10 + (z))

class World
{
public:
	Cube& GetCube(int x, int y, int z);
	void SetCube(int x, int y, int z);
	Chunk& GetChunk(int x, int y, int z);
	void Generate(int seed);
private:
	std::map<int, std::unique_ptr<Chunk>> chunks;
};

