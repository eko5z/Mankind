#pragma once

#include <SDL2/SDL.h>
#include <memory>

class InputMode;

class InputManager
{
public:
	InputManager();
	void ProcessEvents();

	void SetInputMode(std::shared_ptr<InputMode> ptr);
private:
	std::shared_ptr<InputMode> input_mode;
	void ProcessEvent(SDL_Event e);
};

