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
	return *chunks[CHUNK_ID(x, y, z)];
}

void World::Generate(int seed)
{
	LOG("Generating world");
	for (int i(0); i < 4; ++i) {
		for (int j(0); j < 4; ++j) {
			for (int k(0); k < 4; ++k) {
				int s = seed + i * j * k;
				int chunk_id = CHUNK_ID(i, j, k);
				std::unique_ptr<Chunk> new_chunk = std::make_unique<Chunk>();
				chunks.emplace(chunk_id, std::move(new_chunk));
				chunks[chunk_id]->Generate(s);
			}
		}
	}
}

