#include "ChunkMesh.hpp"

#include <glm/glm.hpp>

#include "Log.hpp"

#define INDEX(x, y, z) ((z) * (CHUNK_SIZE+1) * (CHUNK_SIZE+1) + (y) * (CHUNK_SIZE+1) + (x))

ChunkMesh::ChunkMesh(Chunk& chunk, int x, int y, int z) :
	chunk(chunk),
	mesh(nullptr),
	x(x), y(y), z(z)
{
	/* We only need to generate vertices once*/
	/* They could be static, too */
	for (int i(0); i <= CHUNK_SIZE; ++i) {
		for (int j(0); j <= CHUNK_SIZE; ++j) {
			for (int k(0); k <= CHUNK_SIZE; ++k) {
				vertices.push_back(glm::vec3(i, j, k));
			}
		}
	}
}

void ChunkMesh::Update()
{
	chunk.SetClean();

	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;
	std::vector<GLuint> indices;

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

					/* -X or left face = 0,1,2 and 1,2,3*/
					indices.push_back(v_indices[0]);
					indices.push_back(v_indices[1]);
					indices.push_back(v_indices[2]);

					indices.push_back(v_indices[1]);
					indices.push_back(v_indices[2]);
					indices.push_back(v_indices[3]);

					/* +X or right face = same as -X but +4 so 4,5,6 and 5,6,7*/
					indices.push_back(v_indices[4]);
					indices.push_back(v_indices[5]);
					indices.push_back(v_indices[6]);

					indices.push_back(v_indices[5]);
					indices.push_back(v_indices[6]);
					indices.push_back(v_indices[7]);

					/* -Y or front face = 0,2,6 and 0,4,6 */
					indices.push_back(v_indices[0]);
					indices.push_back(v_indices[2]);
					indices.push_back(v_indices[6]);

					indices.push_back(v_indices[0]);
					indices.push_back(v_indices[4]);
					indices.push_back(v_indices[6]);

					/* +Y or back face = same as -Y but +1 so 1,3,7 and 1,5,7 */
					indices.push_back(v_indices[1]);
					indices.push_back(v_indices[3]);
					indices.push_back(v_indices[7]);

					indices.push_back(v_indices[1]);
					indices.push_back(v_indices[5]);
					indices.push_back(v_indices[7]);

					/* -Z or bottom face = 0,1,5 and 0,4,5 */
					indices.push_back(v_indices[0]);
					indices.push_back(v_indices[1]);
					indices.push_back(v_indices[5]);

					indices.push_back(v_indices[0]);
					indices.push_back(v_indices[4]);
					indices.push_back(v_indices[5]);

					/* +Z or bottom face = same as -Z but +2 so 2,3,7 and 2,6,7 */
					indices.push_back(v_indices[2]);
					indices.push_back(v_indices[3]);
					indices.push_back(v_indices[7]);

					indices.push_back(v_indices[2]);
					indices.push_back(v_indices[6]);
					indices.push_back(v_indices[7]);

				}
			}
		}
	}


	this->mesh = std::make_unique<Mesh>(vertices, normals, uvs, indices, "res/tex/stone.png");
	this->mesh->Initialize();
}

void ChunkMesh::Render()
{
	if (chunk.IsDirty()) {
		Update();
	}

	this->mesh->Render();
}

