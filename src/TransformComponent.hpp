#pragma once

#include <glm/glm.hpp>

struct TransformComponent {
	glm::vec3 position, rotation, scale;
	TransformComponent(): position(0, 0, 0), rotation(0, 0, 0), scale(0, 0, 0) {}
	TransformComponent(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale): position(position), rotation(rotation), scale(scale) {}
};

