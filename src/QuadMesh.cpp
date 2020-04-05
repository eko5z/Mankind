#include "QuadMesh.hpp"

//   2---4
//   |\  |
//   | \ |
//   |  \|
//   1___3

#define v1 glm::vec3{-1.0, -1.0, 0.0}
#define v2 glm::vec3{-1.0, 1.0, 0.0}
#define v3 glm::vec3{1.0, -1.0, 0.0}
#define v4 glm::vec3{1.0, 1.0, 0.0}

#define UV_BOTTOM_LEFT  {0, 1}
#define UV_BOTTOM_RIGHT {1, 1}
#define UV_TOP_LEFT     {0, 0}
#define UV_TOP_RIGHT    {1, 0}

#define vertices std::vector<glm::vec3>{v1, v2, v3, v3, v2, v4}
#define normals std::vector<glm::vec3>(6, glm::vec3{0.0, 0.0, -1.0})
#define uvs std::vector<glm::vec2>{UV_BOTTOM_LEFT, UV_TOP_LEFT, UV_BOTTOM_RIGHT, UV_BOTTOM_RIGHT, UV_TOP_LEFT, UV_TOP_RIGHT}
#define indices std::vector<GLuint>{0, 1, 2, 3, 4, 5}

QuadMesh::QuadMesh(std::shared_ptr<Texture> diffuse, std::shared_ptr<Texture> specular):
	Mesh::Mesh(vertices, normals, uvs, indices, diffuse, specular)
{

}
