#pragma once

#include "Mesh.hpp"

class QuadMesh: public Mesh
{
public:
  QuadMesh(std::shared_ptr<Texture> diffuse, std::shared_ptr<Texture> specular);
};
