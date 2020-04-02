#include "Chunk.hpp"

#include <cstdlib>

#include "Log.hpp"

Chunk::Chunk() :
	empty(true)
{
	LOG("Created new chunk");
}

void Chunk::Generate(int x, int y, int z)
{
	this->x = x;
	this->y = y;
	this->z = z;

	for (int i(0); i < CHUNK_SIZE; ++i) {
		for (int j(0); j < CHUNK_SIZE; ++j) {
			for (int k(0); k < CHUNK_SIZE; ++k) {
				SetCube(i, j, k, Cube{0});
			}
		}
	}
}

