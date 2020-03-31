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
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
}

Renderer::~Renderer()
{
	LOG("Destroying renderer");
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Renderer::OpenWindow()
{
	LOG("Opening window");
	window = SDL_CreateWindow(PACKAGE_STRING,
	                          SDL_WINDOWPOS_CENTERED,
	                          SDL_WINDOWPOS_CENTERED,
	                          500, 500,
	                          SDL_WINDOW_SHOWN |
	                          SDL_WINDOW_OPENGL);
	if (window == nullptr) {
		throw std::runtime_error(SDL_GetError());
	}
	context = SDL_GL_CreateContext(window);
	if (context == nullptr) {
		throw std::runtime_error(SDL_GetError());
	}
}

void Renderer::Render(World& world, Camera& camera)
{
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapWindow(window);
}

