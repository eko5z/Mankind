#include "World.hpp"

#include "Log.hpp"

Cube& World::GetCube(int x, int y, int z)
{
}

void World::SetCube(int x, int y, int z)
{
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
	LOG("Load chunk--");
	LOG(id);

	std::unique_ptr<Chunk> new_chunk;
	new_chunk = std::make_unique<Chunk>();
	LOG("emplacing");
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

