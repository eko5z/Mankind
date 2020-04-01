#include <iostream>
#include <config.h>
#include <memory>
#include <cstdlib>
#include <ctime>

#include "Renderer.hpp"
#include "Game.hpp"
#include "MainInputManager.hpp"
#include "InputSystem.hpp"

int main()
{
	std::cout << PACKAGE_STRING << std::endl;
	Renderer renderer;
	Game g;

	renderer.OpenWindow();

	InputSystem input_system;
	input_system.SetInputManager(std::make_unique<MainInputManager>(g));

	g.GetWorld().Generate(0);
	SDL_SetRelativeMouseMode(SDL_TRUE);

	while (g.KeepGoing()) {
		input_system.ProcessEvents();
		renderer.Render(g.GetWorld(), g.GetCamera());
	}

	return 0;
}

