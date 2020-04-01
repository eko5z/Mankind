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
		LoadChunk(id);
	}
	return *chunks[id];
}

void World::LoadChunk(int id)
{
	std::unique_ptr<Chunk> new_chunk = std::make_unique<Chunk>();
	chunks.emplace(id, std::move(new_chunk));
	chunks[id]->Generate(seed * id % 10000007);
}

void World::Generate(int s)
{
	seed = s;
	LOG("Generating world");
	for (int i(0); i < 4; ++i) {
		for (int j(0); j < 4; ++j) {
			for (int k(0); k < 4; ++k) {
				int chunk_id = CHUNK_ID(i, j, k);
				LoadChunk(CHUNK_ID(i, j, k));
			}
		}
	}
}

