#pragma once

#include <sstream>

#include <glm/glm.hpp>

#include "Program.hpp"

class DirectionalLight
{
private:
public:
	glm::vec3 direction;
	glm::vec3 ambient, diffuse, specular;

	DirectionalLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
	void AddToProgram(Program &program, GLuint index);
};
