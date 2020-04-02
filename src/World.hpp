#pragma once

#include "Chunk.hpp"
#include "WorldGenerator.hpp"
#include <map>
#include <tuple>
#include <memory>

#define N_CHUNKS 1024
#define CHUNK_ID(x, y, z) ((z) * N_CHUNKS * N_CHUNKS + (y) * N_CHUNKS + (x))

class World
{
public:
	Cube& GetCube(int x, int y, int z);
	void SetCube(int x, int y, int z);
	Chunk& GetChunk(int x, int y, int z);
	void Generate(int seed);
private:
	std::map<int, std::unique_ptr<Chunk>> chunks;
	void LoadChunk(int, int, int);
	int seed;
	std::unique_ptr<WorldGenerator> world_generator;
};

