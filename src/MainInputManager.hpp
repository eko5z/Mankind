#pragma once

#include <glm/glm.hpp>

#include "GraphX.hpp"
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
	bool is_pointing;
	bool going_forward, going_backward, going_leftward, going_rightward;
	bool jumping;
	bool wireframe;
	glm::vec3 pointed_cube;
	glm::vec3 pointed_normal;
	void ChangePlayerVelocity();
};

