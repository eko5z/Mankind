#pragma once

#include <glm/glm.hpp>

struct TransformComponent
{
	glm::vec3 pos, rot;
	TransformComponent() : pos(0,0,0), rot(0,0,0) {}
	TransformComponent(glm::vec3 pos, glm::vec3 rot) : pos(pos), rot(rot) {}
};

