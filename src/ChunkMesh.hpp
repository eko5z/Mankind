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
	std::shared_ptr<Texture> texture;
	glm::vec2 bottom_left{0, 0},
	    bottom_right{1, 0},
	    top_left{0, 1},
	    top_right{1, 1};
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;
	std::vector<GLuint> indices;
	void PushFace(int v0, int v1, int v2, int v3);
public:
	ChunkMesh(Chunk& chunk, int x, int y, int z, std::shared_ptr<Texture> texture);
	void Render();

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

