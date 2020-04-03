#include "World.hpp"

#include "Log.hpp"
#include "TransformComponent.hpp"
#include "PhysicsSystem.hpp"

#include <cmath>

void World::CreatePlayer()
{
	player = ecs_world->create();
	player->assign<TransformComponent>();
}

World::World() :
	ecs_world(ECS::World::createWorld())
{
	ecs_world->registerSystem(new PhysicsSystem());
	CreatePlayer();
}

World::~World()
{
	ecs_world->destroyWorld();
}

void World::Update(float dt)
{
	ecs_world->tick(dt);
}

Cube& World::GetCube(int x, int y, int z)
{
	int cx(floor((float)x / CHUNK_SIZE)),
	    cy(floor((float)y / CHUNK_SIZE)),
	    cz(floor((float)z / CHUNK_SIZE));
	int ix( ((x % CHUNK_SIZE) + CHUNK_SIZE) % CHUNK_SIZE),
	    iy( ((y % CHUNK_SIZE) + CHUNK_SIZE) % CHUNK_SIZE),
	    iz( ((z % CHUNK_SIZE) + CHUNK_SIZE) % CHUNK_SIZE);
	Chunk& c = GetChunk(cx, cy, cz);
	return c.GetCube(ix, iy, iz);
}

void World::SetCube(int x, int y, int z, Cube cu)
{
	int cx(floor((float)x / CHUNK_SIZE)),
	    cy(floor((float)y / CHUNK_SIZE)),
	    cz(floor((float)z / CHUNK_SIZE));
	int ix( ((x % CHUNK_SIZE) + CHUNK_SIZE) % CHUNK_SIZE),
	    iy( ((y % CHUNK_SIZE) + CHUNK_SIZE) % CHUNK_SIZE),
	    iz( ((z % CHUNK_SIZE) + CHUNK_SIZE) % CHUNK_SIZE);
	Chunk& c = GetChunk(cx, cy, cz);
	c.SetCube(ix, iy, iz, cu);
}

Chunk& World::GetChunk(int x, int y, int z)
{
	int id = CHUNK_ID(x, y, z);
	if (chunks.find(id) == chunks.end()) {
		LoadChunk(x, y, z);
	}
	return *chunks[id];
}

void World::LoadChunk(int x, int y, int z)
{
	int id = CHUNK_ID(x, y, z);

	std::unique_ptr<Chunk> new_chunk;
	new_chunk = std::make_unique<Chunk>();
	chunks.emplace(id, std::move(new_chunk));

	chunks[id]->Generate(x, y, z);
	world_generator->GenerateChunk(*chunks[id]);
}

void World::Generate(int s)
{
	seed = s;
	world_generator = std::make_unique<WorldGenerator>(seed);
	LOG("Generating world");
	for (int i(0); i < 4; ++i) {
		for (int j(0); j < 4; ++j) {
			for (int k(0); k < 4; ++k) {
				LoadChunk(i, j, k);
			}
		}
	}
}

