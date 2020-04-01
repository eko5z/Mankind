#pragma once

#include "InputManager.hpp"

class MainInputManager : public InputManager
{
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
};

