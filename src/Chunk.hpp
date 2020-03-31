#pragma once
#include "Cube.hpp"

#define CHUNK_SIZE 16
#define CHUNK_INCOORD(x, y, z) \
	((x) * CHUNK_SIZE * CHUNK_SIZE + (y) * CHUNK_SIZE + (z))

class Chunk
{
public:
	Cube& GetCube(int x, int y, int z)
	{
		return cubes[CHUNK_INCOORD(x, y, z)];
	}
	void SetCube(int x, int y, int z, Cube& c)
	{
		cubes[CHUNK_INCOORD(x, y, z)] = c;
		dirty = true;
	}
	void SetClean()
	{
		dirty = false;
	}
	bool IsDirty()
	{
		return dirty;
	}
private:
	Cube cubes[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];
	bool dirty;
};

