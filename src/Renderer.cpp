#include "Renderer.hpp"

#include <stdexcept>
#include <config.h>

#include "Log.hpp"

Renderer::Renderer() :
	window(nullptr)
{
	LOG("Initializing renderer");
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		throw std::runtime_error(SDL_GetError());
	}
}

Renderer::~Renderer()
{
	LOG("Destroying renderer");
	SDL_Quit();
}

void Renderer::OpenWindow()
{
	LOG("Opening window");
	window = SDL_CreateWindow("Mankind" PACKAGE_STRING,
	                          SDL_WINDOWPOS_CENTERED,
	                          SDL_WINDOWPOS_CENTERED,
	                          500, 500, SDL_WINDOW_SHOWN);
}

