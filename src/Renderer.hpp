#pragma once

#include <SDL2/SDL.h>
#include "GraphX.hpp"
#include "Game.hpp"
#include "Camera.hpp"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void OpenWindow();
	void Render(World& world, Camera& camera);
private:
	SDL_Window* window;
	SDL_GLContext context;
};

