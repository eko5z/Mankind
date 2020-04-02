#include "ChunkMesh.hpp"

#include <glm/glm.hpp>

#include "Log.hpp"

#define INDEX(x, y, z) ((z) * (CHUNK_SIZE+1) * (CHUNK_SIZE+1) + (y) * (CHUNK_SIZE+1) + (x))

ChunkMesh::ChunkMesh(Chunk& chunk, int x, int y, int z, std::shared_ptr<Texture> diffuse, std::shared_ptr<Texture> specular) :
	chunk(chunk),
	mesh(nullptr),
	x(x), y(y), z(z),
	tile_manager(2),
	diffuse(std::move(diffuse)),
	specular(std::move(specular))
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
void ChunkMesh::PushFace(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 norm, int typeID)
{
	for (int i(0); i < 6; ++i) {
		normals.push_back(norm);
	}

	glm::vec2 top_right    = tile_manager.GetTileTopRight(typeID),
	          top_left     = tile_manager.GetTileTopLeft(typeID),
	          bottom_left  = tile_manager.GetTileBottomLeft(typeID),
	          bottom_right = tile_manager.GetTileBottomRight(typeID);

	real_vertices.push_back(v0);
	indices.push_back(global_index++);
	uvs.push_back(top_left);     // v0

	real_vertices.push_back(v1);
	indices.push_back(global_index++);
	uvs.push_back(top_right);    // v1

	real_vertices.push_back(v2);
	indices.push_back(global_index++);
	uvs.push_back(bottom_left);  // v2

	//--

	real_vertices.push_back(v3);
	indices.push_back(global_index++);
	uvs.push_back(bottom_right); // v3

	real_vertices.push_back(v2);
	indices.push_back(global_index++);
	uvs.push_back(bottom_left);  // v2

	real_vertices.push_back(v1);
	indices.push_back(global_index++);
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

	global_index = 0;
	real_indices.clear();
	real_vertices.clear();
	uvs.clear();
	normals.clear();

	for (int i(0); i <= 15; ++i) {
		for (int j(0); j <= 15; ++j) {
			for (int k(0); k <= 15; ++k) {
				int typeID = chunk.GetCube(i, j, k).typeID;
				if (typeID != 0) {
					/* Aliasing the vertices will make it easier */
					glm::vec3 vertex_alias[8] = {
						vertices[INDEX(i,   j,   k  )], // 0
						vertices[INDEX(i,   j,   k+1)], // 1
						vertices[INDEX(i,   j+1, k  )], // 2
						vertices[INDEX(i,   j+1, k+1)], // 3
						vertices[INDEX(i+1, j,   k  )], // 4
						vertices[INDEX(i+1, j,   k+1)], // 5
						vertices[INDEX(i+1, j+1, k  )], // 6
						vertices[INDEX(i+1, j+1, k+1)], // 7
					};

					if ((i > 0 and chunk.GetCube(i-1, j, k).typeID == 0) or i == 0) {
						/* -X or left face
							3 2
							1 0
						*/
						PushFace(vertex_alias[3],
						         vertex_alias[2],
						         vertex_alias[1],
						         vertex_alias[0],
						         glm::vec3(-1, 0, 0),
						         typeID);
					}

					if ((i < 15 and chunk.GetCube(i+1, j, k).typeID == 0) or i == 15) {
						/* +X or right face
							6 7
							4 5
						*/
						PushFace(vertex_alias[6],
						         vertex_alias[7],
						         vertex_alias[4],
						         vertex_alias[5],
						         glm::vec3(+1, 0, 0),
						         typeID);
					}

					if ((k > 0 and chunk.GetCube(i, j, k-1).typeID == 0) or k == 0) {
						/* -Z or front face
							2 6
							0 4
						*/
						PushFace(vertex_alias[2],
						         vertex_alias[6],
						         vertex_alias[0],
						         vertex_alias[4],
						         glm::vec3(0, 0, -1),
						         typeID);
					}

					if ((k < 15 and chunk.GetCube(i, j, k+1).typeID == 0) or k == 15) {
						/* +Z or back face
							7 3
							5 1
						*/
						PushFace(vertex_alias[7],
						         vertex_alias[3],
						         vertex_alias[5],
						         vertex_alias[1],
						         glm::vec3(0, 0, +1),
						         typeID);
					}

					if ((j > 0 and chunk.GetCube(i, j-1, k).typeID == 0) or j == 0) {
						/* -Y or bottom face
							0 4
							1 5
						*/
						PushFace(vertex_alias[0],
						         vertex_alias[4],
						         vertex_alias[1],
						         vertex_alias[5],
						         glm::vec3(0, -1, 0),
						         typeID);
					}

					if ((j < 15 and chunk.GetCube(i, j+1, k).typeID == 0) or j == 15) {
						/* +Y or top face
							3 7
							2 6
						*/
						PushFace(vertex_alias[3],
						         vertex_alias[7],
						         vertex_alias[2],
						         vertex_alias[6],
						         glm::vec3(0, +1, 0),
						         typeID);
					}
				}
			}
		}
	}


	this->mesh = std::make_unique<Mesh>(real_vertices, normals, uvs, indices, diffuse, specular);
	this->mesh->Initialize();
}

void ChunkMesh::Render()
{
	if (chunk.IsDirty()) {
		Update();
	}

	this->mesh->Render();
}

