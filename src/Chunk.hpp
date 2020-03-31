#pragma once
#include "Cube.hpp"

#define CHUNK_INCOORD(x, y, z) ((x) * 256 + (y) * 16 + (z))

class Chunk
{
public:
	Cube& GetCube(int x, int y, int z)
	{
		return cubes[CHUNK_INCOORD(x, y, z)];
	}
private:
	Cube cubes[16*16*16];
};

