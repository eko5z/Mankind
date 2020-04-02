#pragma once

#include "Chunk.hpp"
#include <map>
#include <tuple>
#include <memory>

#define N_CHUNKS 1<<10
#define CHUNK_ID(x, y, z) ((x) * CHUNK_SIZE * CHUNK_SIZE + (y) * CHUNK_SIZE + (z))

class World
{
public:
	Cube& GetCube(int x, int y, int z);
	void SetCube(int x, int y, int z);
	Chunk& GetChunk(int x, int y, int z);
	void Generate(int seed);
private:
	std::map<int, std::unique_ptr<Chunk>> chunks;
	void LoadChunk(int);
	int seed;
};

