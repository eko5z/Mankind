#pragma once
#include "Cube.hpp"

#define CHUNK_SIZE 16
#define CHUNK_INCOORD(x, y, z) \
	((z) * CHUNK_SIZE * CHUNK_SIZE + (y) * CHUNK_SIZE + (x))

class Chunk
{
public:
	Chunk();
	Cube& GetCube(int x, int y, int z)
	{
		return cubes[CHUNK_INCOORD(x, y, z)];
	}
	void SetCube(int x, int y, int z, Cube c)
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
	void Generate(int x, int y, int z);
	int GetX()
	{
		return x;
	}
	int GetY()
	{
		return y;
	}
	int GetZ()
	{
		return z;
	}
private:
	Cube cubes[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];
	bool dirty;
	int x, y, z;
};

