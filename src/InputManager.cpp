#include "InputManager.hpp"
#include "InputMode.hpp"
#include "Log.hpp"

InputManager::InputManager() :
	input_mode(nullptr)
{
}

void InputManager::ProcessEvent(SDL_Event e)
{
	if (input_mode->LockMouse()) {
	}
	MouseButton mb;
	switch (e.type) {
	case SDL_QUIT:
		LOG("Quit event");
		input_mode->OnQuit();
		break;

	case SDL_KEYUP:
		input_mode->OnKeyUp(e.key.keysym.sym);
		break;

	case SDL_KEYDOWN:
		input_mode->OnKeyDown(e.key.keysym.sym, e.key.repeat);
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
		input_mode->OnMouseButtonDown(mb);
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
		input_mode->OnMouseButtonUp(mb);
		break;

	case SDL_MOUSEMOTION:
		input_mode->OnMouseMotion(e.motion.x, e.motion.y, e.motion.xrel, e.motion.yrel);
	}
}

void InputManager::SetInputMode(std::shared_ptr<InputMode> ptr)
{
input_mode = ptr;
if (input_mode->LockMouse() ){
	SDL_SetRelativeMouseMode(SDL_TRUE);
} else {
	SDL_SetRelativeMouseMode(SDL_FALSE);
}

}

void InputManager::ProcessEvents()
{
	SDL_Event e;
	if (input_mode->LockMouse()) {

	}
	while (SDL_PollEvent(&e)) {
		ProcessEvent(e);
	}
}

