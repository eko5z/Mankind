#include "Chunk.hpp"

#include <cstdlib>

#include "Log.hpp"

Chunk::Chunk(int x, int y, int z) :
	x(x), y(y), z(z),
	empty(true)
{
	for (int i(0); i < CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE; ++i) {
		cubes[i] = Cube{0};
	}
}
