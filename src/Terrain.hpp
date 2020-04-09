#pragma once

#include "Chunk.hpp"
#include "TerrainGenerator.hpp"
#include <map>
#include <tuple>
#include <memory>

#define CHUNK_ID(x, y, z)\
	(0xffff000000000000 & ((int64_t)(x) << 48)) |\
	(0x0000ffff00000000 & ((int64_t)(y) << 32)) |\
	(0x00000000ffff0000 & ((int64_t)(z) << 16))

class Terrain
{
public:
	Cube& GetCube(int x, int y, int z);
	void SetCube(int x, int y, int z, Cube c);
	Chunk& GetChunk(int x, int y, int z);
	void Update(float dt);
	int GetSpawnHeight(int x, int z);
	void SetTerrainGenerator(std::unique_ptr<TerrainGenerator> tg)
	{
		terrain_generator = std::move(tg);
	}

private:
	std::map<uint64_t, std::unique_ptr<Chunk>> chunks;
	void LoadChunk(int, int, int);
	std::unique_ptr<TerrainGenerator> terrain_generator;
	int seed;
};

