#pragma once

#include "InputManager.hpp"

#include <SDL2/SDL.h>

class InputSystem
{
public:
	InputSystem();
	void ProcessEvents();

	void SetInputManager(std::unique_ptr<InputManager> ptr)
	{
		input_manager = std::move(ptr);
	}
private:
	std::unique_ptr<InputManager> input_manager;
	void ProcessEvent(SDL_Event e);
};

