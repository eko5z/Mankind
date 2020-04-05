#include "Mesh.hpp"

#include "Log.hpp"

Mesh::Mesh(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals,
           std::vector<glm::vec2> uvs, std::vector<unsigned int> indices, std::shared_ptr<Texture> diffuse,
           std::shared_ptr<Texture> specular):
	diffuse(nullptr),
	specular(nullptr)
{
	this->vertices = vertices;
	this->normals = normals;
	this->uvs = uvs;
	this->indices = indices;

	if (diffuse != nullptr) {
		this->diffuse = std::move(diffuse);
	} else {
		this->diffuse = nullptr;
	}

	if (specular != nullptr) {
		this->specular = std::move(specular);
	} else {
		this->specular = nullptr;
	}

	//// Put the mesh into OpenGL.
	
	// Generate the VAO.
	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);

	/// Generate the buffer objects.

	// VBO
	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(glm::vec3), &this->vertices[0], GL_STATIC_DRAW);

	// NBO
	glGenBuffers(1, &this->NBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->NBO);
	glBufferData(GL_ARRAY_BUFFER, this->normals.size() * sizeof(glm::vec3), &this->normals[0], GL_STATIC_DRAW);

	// UVBO
	glGenBuffers(1, &this->UVBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->UVBO);
	glBufferData(GL_ARRAY_BUFFER, this->uvs.size() * sizeof(glm::vec2), &this->uvs[0], GL_STATIC_DRAW);

	// EBO
	glGenBuffers(1, &this->EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW);

	/// Set up the vertex attributes.

	// VBO
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

	// NBO
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, this->NBO);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

	// UVBO
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, this->UVBO);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);
}

Mesh::~Mesh()
{
	// Delete the buffer objects.
	glDeleteBuffers(1, &this->VBO);
	glDeleteBuffers(1, &this->NBO);
	glDeleteBuffers(1, &this->UVBO);
	glDeleteBuffers(1, &this->EBO);

	// Delete the vertex array.
	glDeleteVertexArrays(1, &this->VAO);
}

void Mesh::Render()
{
	// Activate diffuse texture.

	if(this->diffuse != nullptr) {
		glActiveTexture(GL_TEXTURE0);
		diffuse->Bind();
	}

	// Activate specular texture.
	if(this->specular != nullptr) {
		glActiveTexture(GL_TEXTURE1);
		specular->Bind();
	}

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);

	glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, (void*) 0);

	glBindVertexArray(0);
}
