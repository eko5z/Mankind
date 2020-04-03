#pragma once

#include <glm/glm.hpp>

#include "InputManager.hpp"

class MainInputManager : public InputManager
{
public:
	using InputManager::InputManager;
	void OnKeyDown(char key);
	void OnKeyUp(char key);
	void OnMouseButtonDown(MouseButton button);
	void OnMouseButtonUp(MouseButton button);
	void OnMouseMotion(int x, int y, int dx, int dy);
	void OnQuit();
	bool LockMouse()
	{
		return true;
	}
private:
	void CalculatePointing(World& world, glm::vec3 position, glm::vec3 lookAt, float maxDistance);
	bool is_pointing;
	glm::vec3 pointed_cube;
	glm::vec3 pointed_normal;
};

