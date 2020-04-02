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
					glm::vec2 bottom_left{0, 0};
					glm::vec2 bottom_right{1, 0};
					glm::vec2 top_left{0, 1};
					glm::vec2 top_right{1, 1};

					if ((i > 0 and chunk.GetCube(i-1, j, k).typeID == 0) or i == 0) {
						/* -X or left face = 0,1,2 and 1,2,3*/
						indices.push_back(v_indices[0]);
						indices.push_back(v_indices[1]);
						indices.push_back(v_indices[2]);

						indices.push_back(v_indices[1]);
						indices.push_back(v_indices[2]);
						indices.push_back(v_indices[3]);

						uvs.push_back(bottom_right);
						uvs.push_back(bottom_left);
						uvs.push_back(top_right);
						uvs.push_back(bottom_left);
						uvs.push_back(top_right);
						uvs.push_back(top_left);
					}

					if (true or (i < 15 and chunk.GetCube(i+1, j, k).typeID == 0) or i == 15) {
						/* +X or right face = same as -X but +4 so 4,5,6 and 5,6,7*/
						indices.push_back(v_indices[4]);
						indices.push_back(v_indices[5]);
						indices.push_back(v_indices[6]);

						indices.push_back(v_indices[5]);
						indices.push_back(v_indices[6]);
						indices.push_back(v_indices[7]);
						uvs.push_back(bottom_left);
						uvs.push_back(bottom_right);
						uvs.push_back(top_left);
						uvs.push_back(bottom_right);
						uvs.push_back(top_left);
						uvs.push_back(top_right);
					}

					if ((k > 0 and chunk.GetCube(i, j, k-1).typeID == 0) or k == 0) {
						/* -Z or front face = 0,2,6 and 0,4,6 */
						indices.push_back(v_indices[0]);
						indices.push_back(v_indices[2]);
						indices.push_back(v_indices[6]);

						indices.push_back(v_indices[0]);
						indices.push_back(v_indices[4]);
						indices.push_back(v_indices[6]);
						uvs.push_back(bottom_left);
						uvs.push_back(top_left);
						uvs.push_back(top_right);
						uvs.push_back(bottom_left);
						uvs.push_back(bottom_right);
						uvs.push_back(top_right);
					}

					if ((k < 15 and chunk.GetCube(i, j, k+1).typeID == 0) or k == 15) {
						/* +Z or back face = same as -Y but +1 so 1,3,7 and 1,5,7 */
						indices.push_back(v_indices[1]);
						indices.push_back(v_indices[3]);
						indices.push_back(v_indices[7]);

						indices.push_back(v_indices[1]);
						indices.push_back(v_indices[5]);
						indices.push_back(v_indices[7]);
						uvs.push_back(bottom_right);
						uvs.push_back(top_right);
						uvs.push_back(top_left);
						uvs.push_back(bottom_right);
						uvs.push_back(bottom_left);
						uvs.push_back(top_left);
					}

					if ((j > 0 and chunk.GetCube(i, j-1, k).typeID == 0) or j == 0) {
						/* -Y or bottom face = 0,1,5 and 0,4,5 */
						indices.push_back(v_indices[0]);
						indices.push_back(v_indices[1]);
						indices.push_back(v_indices[5]);

						indices.push_back(v_indices[0]);
						indices.push_back(v_indices[4]);
						indices.push_back(v_indices[5]);
						uvs.push_back(top_left);
						uvs.push_back(bottom_left);
						uvs.push_back(bottom_right);
						uvs.push_back(top_left);
						uvs.push_back(top_right);
						uvs.push_back(bottom_right);
					}

					if ((j < 15 and chunk.GetCube(i, j+1, k).typeID == 0) or j == 15) {
						/* +Y or top face = same as -Z but +2 so 2,3,7 and 2,6,7 */
						indices.push_back(v_indices[2]);
						indices.push_back(v_indices[3]);
						indices.push_back(v_indices[7]);

						indices.push_back(v_indices[2]);
						indices.push_back(v_indices[6]);
						indices.push_back(v_indices[7]);
						uvs.push_back(bottom_left);
						uvs.push_back(top_left);
						uvs.push_back(top_right);
						uvs.push_back(bottom_left);
						uvs.push_back(bottom_right);
						uvs.push_back(top_right);
					}

					/* -X or left face = 0,1,2 and 1,2,3*/

					/* +X or right face = same as -X but +4 so 4,5,6 and 5,6,7*/
					// Generate UVs.

					/* -Y or front face = 0,2,6 and 0,4,6 */
					// Generate UVs.

					/* +Y or back face = same as -Y but +1 so 1,3,7 and 1,5,7 */
					// Generate UVs.

					/* -Z or bottom face = 0,1,5 and 0,4,5 */
					// Generate UVs.

					/* +Z or top face = same as -Z but +2 so 2,3,7 and 2,6,7 */
					// Generate UVs.
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

