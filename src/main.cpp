#include <iostream>
#include <config.h>
#include <memory>
#include <cstdlib>
#include <ctime>

#include "Renderer.hpp"
#include "Game.hpp"
#include "Log.hpp"
#include "GraphXManager.hpp"

#include "CrossMesh.hpp"

#include "Controller.hpp"

int main()
{
	std::cout << PACKAGE_STRING << std::endl;

	GraphXManager graphics_manager;
	Game g(graphics_manager);

	Renderer renderer(g, graphics_manager);
	renderer.OpenWindow();

	Controller controller(g, renderer);

	graphics_manager.AddMesh("tree", std::make_unique<CrossMesh>());
	graphics_manager.AddTexture("tree_diffuse", std::make_unique<Texture>("res/tex/tree.png"));
	graphics_manager.AddProgram("billboard", std::make_unique<Program>("res/shaders/default.vert", "res/shaders/billboard.frag"));

	int seed = time(0);

	unsigned int last_time(0), current_time;
	unsigned int accumulator;
	float dt = controller.GetDeltaTime();

	controller.StartUp();
	while (g.KeepGoing()) {
		current_time = SDL_GetTicks();
		accumulator += current_time - last_time;
		last_time = current_time;

		while (accumulator >= controller.GetMSPerTick()) {
			accumulator -= controller.GetMSPerTick();
			controller.Step();
		}

		controller.Render();
	}

	return 0;
}

