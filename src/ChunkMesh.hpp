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
	std::shared_ptr<Texture> diffuse, specular;
	glm::vec2
	bottom_left{0, 0},
	            bottom_right{1, 0},
	            top_left{0, 1},
	            top_right{1, 1};
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;
	std::vector<GLuint> indices;
	std::vector<GLuint> real_indices;
	std::vector<glm::vec3> real_vertices;
	int global_index;
	void PushFace(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 norm);
public:
	ChunkMesh(Chunk& chunk, int x, int y, int z, std::shared_ptr<Texture> diffuse,
	          std::shared_ptr<Texture> specular);
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

