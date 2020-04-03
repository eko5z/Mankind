#pragma once

#include "Chunk.hpp"
#include "WorldGenerator.hpp"
#include <map>
#include <tuple>
#include <memory>
#include "ECS.hpp"

#define N_CHUNKS 1024
#define CHUNK_ID(x, y, z) ((x) * N_CHUNKS * N_CHUNKS + (y) * N_CHUNKS + (z))

class World
{
public:
	World();
	~World();
	Cube& GetCube(int x, int y, int z);
	void SetCube(int x, int y, int z, Cube c);
	Chunk& GetChunk(int x, int y, int z);
	void Generate(int seed);
	void Update(float dt);

private:
	std::map<int, std::unique_ptr<Chunk>> chunks;
	void LoadChunk(int, int, int);
	int seed;
	std::unique_ptr<WorldGenerator> world_generator;
	ECS::Entity* player;
	ECS::World* ecs_world;

	void CreatePlayer();
};

