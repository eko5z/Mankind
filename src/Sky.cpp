#include "Sky.hpp"

Sky::Sky():
	mesh(nullptr)
{

	//   2---4
	//   |\  |
	//   | \ |
	//   |  \|
	//   1___3

	/// Generate the fullscreen quad.
	std::vector<glm::vec3> vertices;

	glm::vec3 v1(-1.0, -1.0, 0.0);
	glm::vec3 v2(-1.0, 1.0, 0.0);
	glm::vec3 v3(1.0, -1.0, 0.0);
	glm::vec3 v4(1.0, 1.0, 0.0);

	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);
	vertices.push_back(v3);
	vertices.push_back(v2);
	vertices.push_back(v4);

	// We don't really need them, but whatever.
	std::vector<glm::vec3> normals;

	normals.push_back(glm::vec3{0.0, 0.0, -1.0});
	normals.push_back(glm::vec3{0.0, 0.0, -1.0});
	normals.push_back(glm::vec3{0.0, 0.0, -1.0});

	normals.push_back(glm::vec3{0.0, 0.0, -1.0});
	normals.push_back(glm::vec3{0.0, 0.0, -1.0});
	normals.push_back(glm::vec3{0.0, 0.0, -1.0});

	std::vector<glm::vec2> uvs;

	uvs.push_back(glm::vec2{0, 0});
	uvs.push_back(glm::vec2{0, 1});
	uvs.push_back(glm::vec2{1, 0});

	uvs.push_back(glm::vec2{0, 1});
	uvs.push_back(glm::vec2{1, 1});
	uvs.push_back(glm::vec2{1, 0});

	std::vector<GLuint> indices;

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);

	indices.push_back(3);
	indices.push_back(4);
	indices.push_back(5);

	this->mesh = std::make_unique<Mesh>(vertices, normals, uvs, indices, nullptr, nullptr);
	this->mesh->Initialize();
}

void Sky::Render()
{
	glDisable(GL_DEPTH_TEST);
	this->mesh->Render();
	glEnable(GL_DEPTH_TEST);
}
