#pragma once

#include <SDL2/SDL.h>

class Renderer
{
public:
	Renderer();
	~Renderer();

	void OpenWindow();
private:
	SDL_Window* window;
};

