#include "Camera.hpp"

glm::vec3 Camera::GetForward()
{	
	return glm::normalize(glm::vec3 {
		sinf(rot.x),
		0,
		cosf(rot.x)
	});
}

glm::vec3 Camera::GetLookAt()
{
	return glm::normalize(glm::vec3 {
		sinf(rot.x) * cosf(rot.y),
		sinf(rot.y),
		cosf(rot.x) * cosf(rot.y)
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

