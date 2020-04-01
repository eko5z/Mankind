#include "ChunkMesh.hpp"

#include <glm/glm.hpp>

#include "Log.hpp"

typedef glm::tvec4<GLbyte> byte4;

ChunkMesh::ChunkMesh(Chunk& chunk) :
	chunk(chunk)
{
}

void ChunkMesh::Update()
{
	chunk.SetClean();
	byte4 vertex[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE * 6 * 6];
	int i = 0;
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
				byte4 v1 = byte4(x,   y,   z,   typeID),
				      v2 = byte4(x,   y,   z+1, typeID),
				      v3 = byte4(x,   y+1, z,   typeID),
				      v4 = byte4(x,   y+1, z+1, typeID),
				      v5 = byte4(x+1, y,   z,   typeID),
				      v6 = byte4(x+1, y,   z+1, typeID),
				      v7 = byte4(x+1, y+1, z,   typeID),
				      v8 = byte4(x+1, y+1, z+1, typeID);

				// -X face
				vertex[i++] = v1;
				vertex[i++] = v2;
				vertex[i++] = v3;
				vertex[i++] = v3;
				vertex[i++] = v2;
				vertex[i++] = v4;

				// +X face
				vertex[i++] = v5;
				vertex[i++] = v6;
				vertex[i++] = v7;
				vertex[i++] = v7;
				vertex[i++] = v5;
				vertex[i++] = v8;

				// -Y face
				vertex[i++] = v1;
				vertex[i++] = v5;
				vertex[i++] = v7;
				vertex[i++] = v7;
				vertex[i++] = v1;
				vertex[i++] = v3;

				// +Y face
				vertex[i++] = v2;
				vertex[i++] = v6;
				vertex[i++] = v8;
				vertex[i++] = v8;
				vertex[i++] = v2;
				vertex[i++] = v4;

				// -Z face
				vertex[i++] = v1;
				vertex[i++] = v2;
				vertex[i++] = v6;
				vertex[i++] = v6;
				vertex[i++] = v2;
				vertex[i++] = v5;

				// +Z face
				vertex[i++] = v3;
				vertex[i++] = v4;
				vertex[i++] = v8;
				vertex[i++] = v8;
				vertex[i++] = v4;
				vertex[i++] = v7;
			}
		}
	}
	elements = i;
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, elements * sizeof *vertex,
	             vertex, GL_STATIC_DRAW);
}

void ChunkMesh::Render(Program& program)
{
	if (chunk.IsDirty()) {
		Update();
	}

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(program.GetAttrib("coord"), 4, GL_BYTE, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, elements);
}

