#pragma once

#include <glm/glm.hpp>

#include "InputManager.hpp"

class MainInputManager : public InputManager
{
public:
	MainInputManager(Game& g);
	void OnKeyDown(char key, bool repeat);
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
	bool going_forward, going_backward, going_leftward, going_rightward;
	bool jumping;
	glm::vec3 pointed_cube;
	glm::vec3 pointed_normal;
	void ChangePlayerVelocity(glm::vec3 player_velocity, glm::vec3 forward, glm::vec3 right);
};

