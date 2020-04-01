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

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;
	std::vector<GLuint> indices;

	// for (int x(0); x < CHUNK_SIZE; ++x) {
	// 	for (int y(0); y < CHUNK_SIZE; ++y) {
	// 		for (int z(0); z < CHUNK_SIZE; ++z) {
	// 			int typeID = chunk.GetCube(x, y, z).typeID;

	// 			if (typeID == 0) {
	// 				continue;
	// 			}

	// 			/*
	// 				Y  Z
	// 				^ /
	// 				|/
	// 				0--> X

	// 			      4 -- 8
	// 			     /|   /|
	// 			    3 +- 7 |
	// 				| |  | |
	// 				| 2 -+ 6
	// 				|/   |/
	// 				1 -- 5
	// 			 */

	// 			// -X face
	// 		        vertices.push_back(glm::vec3{x, y, z});
	// 			vertices.push_back(glm::vec3{x, y, z + 1});
	// 			vertices.push_back(glm::vec3{x, y + 1, z});
	// 			vertices.push_back(glm::vec3{x, y + 1, z});
	// 			vertices.push_back(glm::vec3{x, y, z + 1});
	// 			vertices.push_back(glm::vec3{x, y + 1, z + 1});

	// 			// +X face
	// 			vertices.push_back(glm::vec3{x + 1, y, z});
	// 			vertices.push_back(glm::vec3{x + 1, y, z + 1});
	// 			vertices.push_back(glm::vec3{x + 1, y + 1, z});
	// 			vertices.push_back(glm::vec3{x + 1, y + 1, z});
	// 			vertices.push_back(glm::vec3{x + 1, y, z});
	// 			vertices.push_back(glm::vec3{x + 1, y + 1, z + 1});

	// 			// -Y face
	// 		        vertices.push_back(glm::vec3{x, y, z});
	// 			vertices.push_back(glm::vec3{x + 1, y, z});
	// 			vertices.push_back(glm::vec3{x + 1, y + 1, z});
	// 			vertices.push_back(glm::vec3{x + 1, y + 1, z});
	// 			vertices.push_back(glm::vec3{x, y, z});
	// 			vertices.push_back(glm::vec3{x, y + 1, z});

	// 			// +Y face
	// 		        vertices.push_back(glm::vec3{x, y, z + 1});
	// 			vertices.push_back(glm::vec3{x + 1, y, z + 1});
	// 			vertices.push_back(glm::vec3{x + 1, y + 1, z + 1});
	// 			vertices.push_back(glm::vec3{x + 1, y + 1, z + 1});
	// 			vertices.push_back(glm::vec3{x, y, z + 1});
	// 			vertices.push_back(glm::vec3{x, y + 1, z + 1});

	// 			// -Z face
	// 		        vertices.push_back(glm::vec3{x, y, z});
	// 			vertices.push_back(glm::vec3{x, y, z + 1});
	// 			vertices.push_back(glm::vec3{x + 1, y, z + 1});
	// 			vertices.push_back(glm::vec3{x + 1, y, z + 1});
	// 			vertices.push_back(glm::vec3{x, y, z + 1});
	// 			vertices.push_back(glm::vec3{x + 1, y, z});

	// 			// +Z face
	// 		        vertices.push_back(glm::vec3{x, y + 1, z});
	// 			vertices.push_back(glm::vec3{x, y + 1, z + 1});
	// 			vertices.push_back(glm::vec3{x + 1, y + 1, z + 1});
	// 			vertices.push_back(glm::vec3{x + 1, y + 1, z + 1});
	// 			vertices.push_back(glm::vec3{x, y + 1, z + 1});
	// 			vertices.push_back(glm::vec3{x + 1, y + 1, z});

	// 			// Indices
	// 			indices.push_back(2);
	// 		}
	// 	}
	// }

	for (int i(0); i <= 16; ++i) {
	  for (int j(0); j <= 16; ++j) {
	    for (int k(0); k <= 16; ++k) {
	      vertices.push_back(glm::vec3(i, j, k));
	    }
	  }
	}
	
	for (int i(0); i <= 15; ++i) {
	  for (int j(0); j <= 15; ++j) {
	    for (int k(0); k <= 15; ++k) {
	      int typeID = chunk.GetCube(i, j, k).typeID;
	      
	      if (typeID != 0)
		{
		  indices.push_back(CHUNK_INDEX(i, j, k));
		  indices.push_back(CHUNK_INDEX(i, j, k + 1));
		  indices.push_back(CHUNK_INDEX(i, j + 1, k));
		  indices.push_back(CHUNK_INDEX(i, j + 1, k + 1));
		  indices.push_back(CHUNK_INDEX(i + 1, j, k));
		  indices.push_back(CHUNK_INDEX(i + 1, j, k + 1));
		  indices.push_back(CHUNK_INDEX(i + 1, j + 1, k));
		  indices.push_back(CHUNK_INDEX(i + 1, j + 1, k + 1));
		}
	    }
	  }
	}


	this->mesh = std::make_unique<Mesh>(vertices, normals, uvs, indices);	
	this->mesh->Initialize();
}

void ChunkMesh::Render()
{
	if (chunk.IsDirty()) {
		Update();
	}

	this->mesh->Render();
}

