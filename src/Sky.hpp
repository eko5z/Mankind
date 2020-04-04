#pragma once

#include <glm/glm.hpp>

#include "GraphX.hpp"
#include "Mesh.hpp"

class Sky
{
private:
	std::unique_ptr<Mesh> mesh;
public:
	Sky();

	void Render();
};
