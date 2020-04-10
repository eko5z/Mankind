#include "CrossMesh.hpp"

//   2-6,8-4
//   |\    |
//   |  \  |
//   |    \|
//   1_5,7_3

// The first quad.
#define v1 glm::vec3{-1.0, -1.0, 0.0}
#define v2 glm::vec3{-1.0, 1.0, 0.0}
#define v3 glm::vec3{1.0, -1.0, 0.0}
#define v4 glm::vec3{1.0, 1.0, 0.0}

// And the second quad.
#define v5 glm::vec3{0.0, -1.0, -1.0}
#define v6 glm::vec3{0.0, 1.0, -1.0}
#define v7 glm::vec3{0.0, -1.0, 1.0}
#define v8 glm::vec3{0.0, 1.0, 1.0}

#define UV_BOTTOM_LEFT  {0, 1}
#define UV_BOTTOM_RIGHT {1, 1}
#define UV_TOP_LEFT     {0, 0}
#define UV_TOP_RIGHT    {1, 0}

#define vertices std::vector<glm::vec3>{v1, v2, v3, v3, v2, v4, v5, v6, v7, v7, v6, v8}
#define normals std::vector<glm::vec3>(6, glm::vec3{0.0, 0.0, -1.0})
#define uvs std::vector<glm::vec2>{UV_BOTTOM_LEFT, UV_TOP_LEFT, UV_BOTTOM_RIGHT, UV_BOTTOM_RIGHT, UV_TOP_LEFT, UV_TOP_RIGHT, \
				     UV_BOTTOM_LEFT, UV_TOP_LEFT, UV_BOTTOM_RIGHT, UV_BOTTOM_RIGHT, UV_TOP_LEFT, UV_TOP_RIGHT}
#define indices std::vector<GLuint>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}

CrossMesh::CrossMesh():
	Mesh::Mesh(vertices, normals, uvs, indices)
{

}
