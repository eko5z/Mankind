#pragma once

#include "MouseButton.hpp"
#include "Game.hpp"

class InputManager
{
protected:
	Game& game;
public:
	InputManager(Game& game) : game(game) {}
	virtual void OnKeyDown(char key) = 0;
	virtual void OnKeyUp(char key) = 0;
	virtual void OnMouseButtonDown(MouseButton button) = 0;
	virtual void OnMouseButtonUp(MouseButton button) = 0;
	virtual void OnMouseMotion(int x, int y, int dx, int dy) = 0;
	virtual void OnQuit() = 0;
	virtual bool LockMouse()
	{
		return false;
	}
};

