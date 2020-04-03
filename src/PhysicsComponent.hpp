#pragma once

#include <glm/glm.hpp>

struct PhysicsComponent {
	PhysicsComponent() :
		vel(0,0,0),
		box_whd(0,0,0) {}
	glm::vec3 vel;
	glm::vec3 box_whd; /* width height depth */
};

