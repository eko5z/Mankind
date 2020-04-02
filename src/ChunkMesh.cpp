#include "ChunkMesh.hpp"

#include <glm/glm.hpp>

#include "Log.hpp"

#define INDEX(x, y, z) ((z) * (CHUNK_SIZE+1) * (CHUNK_SIZE+1) + (y) * (CHUNK_SIZE+1) + (x))

ChunkMesh::ChunkMesh(Chunk& chunk, int x, int y, int z, std::shared_ptr<Texture> tex) :
	chunk(chunk),
	mesh(nullptr),
	x(x), y(y), z(z),
	texture(std::move(tex))
{
	/* We only need to generate vertices once*/
	/* They could be static, too */
	for (int i(0); i <= CHUNK_SIZE; ++i) {
		for (int j(0); j <= CHUNK_SIZE; ++j) {
			for (int k(0); k <= CHUNK_SIZE; ++k) {
				this->vertices.push_back(glm::vec3(i, j, k));
			}
		}
	}
}


/*
 Pushes indices as so:

 v0 v1
   /
 v2 v3
*/
void ChunkMesh::PushFace(int v0, int v1, int v2, int v3, glm::vec3 norm)
{
	for (int i(0); i < 6; ++i) {
		normals.push_back(norm);
	}

	indices.push_back(v0);
	indices.push_back(v1);
	indices.push_back(v2);

	uvs.push_back(top_left);     // v0
	uvs.push_back(top_right);    // v1
	uvs.push_back(bottom_left);  // v2

	indices.push_back(v3);
	indices.push_back(v2);
	indices.push_back(v1);

	uvs.push_back(bottom_right); // v3
	uvs.push_back(bottom_left);  // v2
	uvs.push_back(top_right);    // v1
}

void ChunkMesh::Update()
{
	chunk.SetClean();


	/*
		Y  Z
		^ /
		|/
		0--> X

		  3 -- 7
		 /|   /|
		2 +- 6 |
		| |  | |
		| 1 -+ 5
		|/   |/
		0 -- 4
	 */

	for (int i(0); i <= 15; ++i) {
		for (int j(0); j <= 15; ++j) {
			for (int k(0); k <= 15; ++k) {
				int typeID = chunk.GetCube(i, j, k).typeID;
				if (typeID != 0) {
					/* Aliasing the vertices will make it easier */
					unsigned int v_indices[8] = {
						INDEX(i,   j,   k  ), // 0
						INDEX(i,   j,   k+1), // 1
						INDEX(i,   j+1, k  ), // 2
						INDEX(i,   j+1, k+1), // 3
						INDEX(i+1, j,   k  ), // 4
						INDEX(i+1, j,   k+1), // 5
						INDEX(i+1, j+1, k  ), // 6
						INDEX(i+1, j+1, k+1), // 7
					};

					if ((i > 0 and chunk.GetCube(i-1, j, k).typeID == 0) or i == 0) {
						/* -X or left face
							3 2
							1 0
						*/
						PushFace(v_indices[3],
						         v_indices[2],
						         v_indices[1],
						         v_indices[0],
								 glm::vec3(-1, 0, 0));
					}

					if ((i < 15 and chunk.GetCube(i+1, j, k).typeID == 0) or i == 15) {
						/* +X or right face
							6 7
							4 5
						*/
						PushFace(v_indices[6],
						         v_indices[7],
						         v_indices[4],
						         v_indices[5],
								 glm::vec3(+1, 0, 0));
					}

					if ((k > 0 and chunk.GetCube(i, j, k-1).typeID == 0) or k == 0) {
						/* -Z or front face
							2 6
							0 4
						*/
						PushFace(v_indices[2],
						         v_indices[6],
						         v_indices[0],
						         v_indices[4],
								 glm::vec3(0, 0, -1));
					}

					if ((k < 15 and chunk.GetCube(i, j, k+1).typeID == 0) or k == 15) {
						/* +Z or back face
							7 3
							5 1
						*/
						PushFace(v_indices[7],
						         v_indices[3],
						         v_indices[5],
						         v_indices[1],
								 glm::vec3(0, 0, +1));
					}

					if ((j > 0 and chunk.GetCube(i, j-1, k).typeID == 0) or j == 0) {
						/* -Y or bottom face
							0 4
							1 5
						*/
						PushFace(v_indices[0],
						         v_indices[4],
						         v_indices[1],
						         v_indices[5],
								 glm::vec3(0, -1, 0));
					}

					if ((j < 15 and chunk.GetCube(i, j+1, k).typeID == 0) or j == 15) {
						/* +Y or top face
							3 7
							2 6
						*/
						PushFace(v_indices[3],
						         v_indices[7],
						         v_indices[2],
						         v_indices[6],
								 glm::vec3(0, +1, 0));
					}
				}
			}
		}
	}


	this->mesh = std::make_unique<Mesh>(vertices, normals, uvs, indices, texture);
	this->mesh->Initialize();
}

void ChunkMesh::Render()
{
	if (chunk.IsDirty()) {
		Update();
	}

	this->mesh->Render();
}

