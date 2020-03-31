#include "InputSystem.hpp"
#include "Log.hpp"

InputSystem::InputSystem() :
	input_manager(nullptr)
{
}

void InputSystem::ProcessEvent(SDL_Event e)
{
	MouseButton mb;
	switch (e.type) {
	case SDL_QUIT:
		LOG("Quit event");
		input_manager->OnQuit();
		break;

	case SDL_KEYUP:
		input_manager->OnKeyUp(e.key.keysym.sym);
		break;

	case SDL_KEYDOWN:
		input_manager->OnKeyDown(e.key.keysym.sym);
		break;

	case SDL_MOUSEBUTTONDOWN:
		switch (e.button.button) {
		case SDL_BUTTON_LEFT:
			mb = MouseButton::LEFT;
			break;

		case SDL_BUTTON_MIDDLE:
			mb = MouseButton::MIDDLE;
			break;

		case SDL_BUTTON_RIGHT:
			mb = MouseButton::RIGHT;
			break;
		}
		input_manager->OnMouseButtonDown(mb);
		break;

	case SDL_MOUSEBUTTONUP:
		switch (e.button.button) {
		case SDL_BUTTON_LEFT:
			mb = MouseButton::LEFT;
			break;

		case SDL_BUTTON_MIDDLE:
			mb = MouseButton::MIDDLE;
			break;

		case SDL_BUTTON_RIGHT:
			mb = MouseButton::RIGHT;
			break;
		}
		input_manager->OnMouseButtonUp(mb);
		break;
	}

}

void InputSystem::ProcessEvents()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		ProcessEvent(e);
	}
}

