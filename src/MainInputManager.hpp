#pragma once

#include "InputManager.hpp"

class MainInputManager : public InputManager
{
	using InputManager::InputManager;
	void OnKeyDown(char key);
	void OnKeyUp(char key);
	void OnMouseButtonDown(MouseButton button);
	void OnMouseButtonUp(MouseButton button);
	void OnQuit();
};

