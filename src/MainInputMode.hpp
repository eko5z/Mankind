#pragma once

#include <glm/glm.hpp>

#include "InputMode.hpp"

class MainInputMode : public InputMode
{
public:
	using InputMode::InputMode;
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
};

