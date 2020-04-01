#pragma once

#include "GraphX.hpp"
#include "Chunk.hpp"
#include "Program.hpp"

class ChunkMesh
{
private:
	Chunk& chunk;
	GLuint vbo;
	int elements;
	void Update();
public:
	ChunkMesh(Chunk& chunk);
	void Render(Program& program);
};

