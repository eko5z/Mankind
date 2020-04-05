#include "World.hpp"

#include "Log.hpp"

#include <cmath>

void World::Update(float dt)
{
}

int World::GetSpawnHeight(int x, int z)
{
	return world_generator->HeightAt(x, z) + 1;
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
	/* mark adjacent chunks as dirty if cube is modified
	on the edges */
	if (ix == 0) {
		GetChunk(cx - 1, cy, cz).SetDirty();
	} else if (ix == CHUNK_SIZE - 1) {
		GetChunk(cx + 1, cy, cz).SetDirty();
	}
	if (iy == 0) {
		GetChunk(cx, cy - 1, cz).SetDirty();
	} else if (iy == CHUNK_SIZE - 1) {
		GetChunk(cx, cy + 1, cz).SetDirty();
	}
	if (iz == 0) {
		GetChunk(cx, cy, cz - 1).SetDirty();
	} else if (iz == CHUNK_SIZE - 1) {
		GetChunk(cx, cy, cz + 1).SetDirty();
	}
	c.SetCube(ix, iy, iz, cu);
}

Chunk& World::GetChunk(int x, int y, int z)
{
	uint64_t id = CHUNK_ID(x, y, z);
	if (chunks.find(id) == chunks.end()) {
		LoadChunk(x, y, z);
	}
	return *chunks[id];
}

void World::LoadChunk(int x, int y, int z)
{
	int64_t id = CHUNK_ID(x, y, z);

	std::unique_ptr<Chunk> new_chunk;
	new_chunk = std::make_unique<Chunk>();
	chunks.emplace(id, std::move(new_chunk));

	world_generator->GenerateChunk(*chunks[id]);
}

void World::Generate(int s)
{
	seed = s;
	world_generator = std::make_unique<WorldGenerator>(seed);
	LOG("Generating world");
	for (int i(0); i < 4; ++i) {
		for (int j(0); j < 4; ++j) {
			for (int k(GetSpawnHeight(0, 0)); k < GetSpawnHeight(0, 0)+4; ++k) {
				LoadChunk(i, j, k);
			}
		}
	}
}

