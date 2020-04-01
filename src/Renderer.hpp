#pragma once

#include <memory>
#include <SDL2/SDL.h>
#include "GraphX.hpp"
#include "Game.hpp"
#include "Camera.hpp"
#include "Program.hpp"

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
	std::unique_ptr<Program> chunk_program;
};

