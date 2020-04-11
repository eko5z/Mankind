#pragma once

#include "InputMode.hpp"

class GUIInputMode : public InputMode
{
public:
	using InputMode::InputMode;
	virtual void OnKeyDown(char key, bool repeat);
	virtual void OnKeyUp(char key);
	virtual void OnMouseButtonDown(MouseButton button);
	virtual void OnMouseButtonUp(MouseButton button);
	virtual void OnMouseMotion(int x, int y, int dx, int dy);
	virtual void OnQuit();
};

