#pragma once

#include <glm/glm.hpp>

struct Camera {
	unsigned int view_width, view_height;

	glm::vec3 position, rotation;

	glm::vec3 GetForward();
	glm::vec3 GetLookAt();
	glm::vec3 GetRight();
	glm::vec3 GetUp();

	Camera(unsigned int view_width, unsigned int view_height):
		view_width(view_width), view_height(view_height) {}
};

