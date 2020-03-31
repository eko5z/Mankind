#include <iostream>
#include <config.h>
#include <memory>

#include "Renderer.hpp"
#include "Game.hpp"
#include "MainInputManager.hpp"
#include "InputSystem.hpp"

int main()
{
	std::cout << "Starting " << PACKAGE_STRING << std::endl;
	Renderer r;
	Game g;

	r.OpenWindow();

	InputSystem input_system;
	input_system.SetInputManager(std::make_unique<MainInputManager>(g));

	while (g.KeepGoing()) {
		input_system.ProcessEvents();
	}

	return 0;
}

