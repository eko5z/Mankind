#include "ChunkMesh.hpp"

#include <glm/glm.hpp>

#include "Log.hpp"

ChunkMesh::ChunkMesh(Chunk& chunk) :
  chunk(chunk),
  mesh(nullptr)
{
}

void ChunkMesh::Update()
{
	chunk.SetClean();
	int i = -1;
	for (int x(0); x < CHUNK_SIZE; ++x) {
		for (int y(0); y < CHUNK_SIZE; ++y) {
			for (int z(0); z < CHUNK_SIZE; ++z) {
				int typeID = chunk.GetCube(x, y, z).typeID;

				if (typeID == 0) {
					continue;
				}

				/*
					Y  Z
					^ /
					|/
					0--> X

				      4 -- 8
				     /|   /|
				    3 +- 7 |
					| |  | |
					| 2 -+ 6
					|/   |/
					1 -- 5
				 */

				// -X face
				this->mesh->vertices[i++] = glm::vec3{x, y, z};
				this->mesh->vertices[i++] = glm::vec3{x, y, z + 1};
				this->mesh->vertices[i++] = glm::vec3{x, y + 1, z};
				this->mesh->vertices[i++] = glm::vec3{x, y + 1, z};
				this->mesh->vertices[i++] = glm::vec3{x, y, z + 1};
				this->mesh->vertices[i++] = glm::vec3{x, y + 1, z + 1};

				// +X face
				this->mesh->vertices[i++] = glm::vec3{x + 1, y, z};
				this->mesh->vertices[i++] = glm::vec3{x + 1, y, z + 1};
				this->mesh->vertices[i++] = glm::vec3{x + 1, y + 1, z};
				this->mesh->vertices[i++] = glm::vec3{x + 1, y + 1, z};
				this->mesh->vertices[i++] = glm::vec3{x + 1, y, z};
				this->mesh->vertices[i++] = glm::vec3{x + 1, y + 1, z + 1};

				// -Y face
			        this->mesh->vertices[i++] = glm::vec3{x, y, z};
				this->mesh->vertices[i++] = glm::vec3{x + 1, y, z};
				this->mesh->vertices[i++] = glm::vec3{x + 1, y + 1, z};
				this->mesh->vertices[i++] = glm::vec3{x + 1, y + 1, z};
				this->mesh->vertices[i++] = glm::vec3{x, y, z};
				this->mesh->vertices[i++] = glm::vec3{x, y + 1, z};

				// +Y face
			        this->mesh->vertices[i++] = glm::vec3{x, y, z + 1};
				this->mesh->vertices[i++] = glm::vec3{x + 1, y, z + 1};
				this->mesh->vertices[i++] = glm::vec3{x + 1, y + 1, z + 1};
				this->mesh->vertices[i++] = glm::vec3{x + 1, y + 1, z + 1};
				this->mesh->vertices[i++] = glm::vec3{x, y, z + 1};
				this->mesh->vertices[i++] = glm::vec3{x, y + 1, z + 1};

				// -Z face
			        this->mesh->vertices[i++] = glm::vec3{x, y, z};
				this->mesh->vertices[i++] = glm::vec3{x, y, z + 1};
				this->mesh->vertices[i++] = glm::vec3{x + 1, y, z + 1};
				this->mesh->vertices[i++] = glm::vec3{x + 1, y, z + 1};
				this->mesh->vertices[i++] = glm::vec3{x, y, z + 1};
				this->mesh->vertices[i++] = glm::vec3{x + 1, y, z};

				// +Z face
			        this->mesh->vertices[i++] = glm::vec3{x, y + 1, z};
				this->mesh->vertices[i++] = glm::vec3{x, y + 1, z + 1};
				this->mesh->vertices[i++] = glm::vec3{x + 1, y + 1, z + 1};
				this->mesh->vertices[i++] = glm::vec3{x + 1, y + 1, z + 1};
				this->mesh->vertices[i++] = glm::vec3{x, y + 1, z + 1};
				this->mesh->vertices[i++] = glm::vec3{x + 1, y + 1, z};
			}
		}
	}

	this->mesh->Initialize();
}

void ChunkMesh::Render()
{
	if (chunk.IsDirty()) {
		Update();
	}

	this->mesh->Render();
}

