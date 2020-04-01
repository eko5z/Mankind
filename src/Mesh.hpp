#pragma once

#include "GraphX.hpp"

#include <vector>
#include <string>
#include <memory>

#include <glm/glm.hpp>

class Mesh
{
private:
	// Vertex Array Object, Vertex Buffer Object, Normal Buffer Object, UV Buffer Object, Element Buffer Object.
	GLuint VAO, VBO, NBO, UVBO, EBO;
public:
	Mesh(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, std::vector<glm::vec2> uvs, std::vector<GLuint> indices);
	~Mesh();

	void Initialize();
	void Render();

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;
	std::vector<GLuint> indices;
};
