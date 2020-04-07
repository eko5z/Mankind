#include "Camera.hpp"

glm::vec3 Camera::GetForward()
{
	return glm::normalize(glm::vec3 {
		sinf(rotation.x),
		0,
		cosf(rotation.x)
	});
}

glm::vec3 Camera::GetLookAt()
{
	return glm::normalize(glm::vec3 {
		sinf(rotation.x) * cosf(rotation.y),
		sinf(rotation.y),
		cosf(rotation.x) * cosf(rotation.y)
	});

}

glm::vec3 Camera::GetRight()
{
	return glm::cross(GetLookAt(), GetUp());
}

glm::vec3 Camera::GetUp()
{
	return glm::vec3{0.f, 1.f, 0.f};
}

