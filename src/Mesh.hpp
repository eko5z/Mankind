#pragma once

#include <vector>
#include <string>
#include <memory>

#include <glm/glm.hpp>

#include "GraphX.hpp"
#include "Texture.hpp"

class Mesh
{
private:
	// Vertex Array Object, Vertex Buffer Object, Normal Buffer Object, UV Buffer Object, Element Buffer Object.
	GLuint VAO, VBO, NBO, UVBO, EBO;
	// One texture --- for now!
  std::unique_ptr<Texture> texture;
public:
  Mesh(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, std::vector<glm::vec2> uvs, std::vector<GLuint> indices, std::string texture_path);
	~Mesh();

	void Initialize();
	void Render();

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;
	std::vector<GLuint> indices;
};
