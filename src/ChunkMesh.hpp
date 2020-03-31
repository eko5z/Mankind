#pragma once

#include "GraphX.hpp"
#include "Chunk.hpp"

class ChunkMesh
{
private:
	Chunk& chunk;
	GLuint vbo;
	int elements;
	void Update();
public:
	ChunkMesh();
	void Render();
}

