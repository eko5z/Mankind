#pragma once

#include <sstream>

#include <glm/glm.hpp>

#include "Program.hpp"

class DirectionalLight
{
private:
public:
  glm::vec3 direction;
  glm::vec3 ambient_color, diffuse_color;

  DirectionalLight(glm::vec3 direction, glm::vec3 ambient_color, glm::vec3 diffuse_color);
  void AddToProgram(Program &program, GLuint index);
};
