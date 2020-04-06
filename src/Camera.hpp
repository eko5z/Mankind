#pragma once

#include <glm/glm.hpp>

struct Camera {
	glm::vec3 pos;
	glm::vec3 rot;

	glm::vec3 GetForward();
	glm::vec3 GetLookAt();
	glm::vec3 GetRight();
	glm::vec3 GetUp();
};

