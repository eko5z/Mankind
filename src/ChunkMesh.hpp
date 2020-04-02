#pragma once

#include "GraphX.hpp"
#include "Chunk.hpp"
#include "Program.hpp"
#include "Mesh.hpp"

#define CHUNK_INDEX(x, y, z) ((x) * 256 + (y) * 16 + (z))

class ChunkMesh
{
private:
	Chunk& chunk;
	std::unique_ptr<Mesh> mesh;
	void Update();
	std::vector<glm::vec3> vertices;
	int x, y, z;
public:
	ChunkMesh(Chunk& chunk, int x, int y, int z);
	void Render(Program& p);

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
};

