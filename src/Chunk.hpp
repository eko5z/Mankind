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
		if (c.typeID != 0) {
			empty = false;
		}
	}
	void SetClean()
	{
		dirty = false;
	}
	void SetDirty()
	{
		dirty = true;
	}
	bool IsDirty()
	{
		return dirty;
	}
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
	bool IsEmpty()
	{
		return empty;
	}
	void SetEmpty(bool s)
	{
		empty = s;
	}
private:
	Cube cubes[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];
	bool dirty;
	bool empty;
	int x, y, z;
};

