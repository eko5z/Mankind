#pragma once

#include <vector>
#include <string>
#include <memory>

#include <glm/glm.hpp>

#include "GraphX.hpp"
#include "Texture.hpp"
#include "Program.hpp"

class Mesh
{
private:
	// Vertex Array Object, Vertex Buffer Object, Normal Buffer Object, UV Buffer Object, Element Buffer Object.
	GLuint VAO, VBO, NBO, UVBO, EBO;

  std::shared_ptr<Texture> diffuse, specular;
public:
	Mesh(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals,
	     std::vector<glm::vec2> uvs, std::vector<GLuint> indices, std::shared_ptr<Texture> diffuse,
	     std::shared_ptr<Texture> specular);
	~Mesh();

	void Initialize();
	void Render();

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;
	std::vector<GLuint> indices;
};
