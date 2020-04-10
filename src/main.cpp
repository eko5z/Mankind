#include <iostream>
#include <config.h>
#include <memory>
#include <cstdlib>
#include <ctime>

#include "Renderer.hpp"
#include "Game.hpp"
#include "MainInputManager.hpp"
#include "InputSystem.hpp"
#include "Log.hpp"
#include "GraphXManager.hpp"

#include "CrossMesh.hpp"

int main()
{
	std::cout << PACKAGE_STRING << std::endl;

	GraphXManager graphics_manager;
	Game g(graphics_manager);

	Renderer renderer(g, graphics_manager);
	renderer.OpenWindow();

	graphics_manager.AddMesh("tree", std::make_unique<CrossMesh>());
	graphics_manager.AddTexture("tree_diffuse", std::make_unique<Texture>("res/tex/tree.png"));
	graphics_manager.AddProgram("billboard", std::make_unique<Program>("res/shaders/default.vert", "res/shaders/billboard.frag"));


	InputSystem input_system;
	input_system.SetInputManager(std::make_unique<MainInputManager>(g));

	int seed = time(0);

	SDL_SetRelativeMouseMode(SDL_TRUE);

	unsigned int last_time(0), current_time;
	const unsigned int MS_PER_TICK = 25;
	unsigned int accumulator;
	float dt = MS_PER_TICK / 1000.f;

	g.Start(seed);
	while (g.KeepGoing()) {
		current_time = SDL_GetTicks();
		accumulator += current_time - last_time;
		last_time = current_time;

		while (accumulator >= MS_PER_TICK) {
			accumulator -= MS_PER_TICK;
			input_system.ProcessEvents();
			g.Update(dt);
		}

		renderer.Render();
	}

	return 0;
}

