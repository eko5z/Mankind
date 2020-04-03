#pragma once

#include <glm/glm.hpp>

#include "Mesh.hpp"

class Sky
{
private:
  std::unique_ptr<Mesh> mesh;
  Program program;
public:
  Sky();

  void Render();
};
