#include "Sky.hpp"

Sky::Sky():
	mesh(nullptr),
	program("res/shaders/sky.vert", "res/shaders/sky.frag")
{

	//   +---+
	//   |\  |
	//   | \ |
	//   |  \|
	//   +___+

	/// Generate the fullscreen quad.
	std::vector<glm::vec3> vertices;

	vertices.push_back(glm::vec3{-1.0, -1.0, 0.0});
	vertices.push_back(glm::vec3{-1.0, 1.0, 0.0});
	vertices.push_back(glm::vec3{1.0, -1.0, 0.0});

	vertices.push_back(glm::vec3{-1.0, 1.0, 0.0});
	vertices.push_back(glm::vec3{1.0, 1.0, 0.0});
	vertices.push_back(glm::vec3{1.0, -1.0, 0.0});

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

	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(3);

	indices.push_back(4);
	indices.push_back(5);
	indices.push_back(6);
}

void Sky::Render()
{
	this->program.Use();
	this->mesh->Render();
}
