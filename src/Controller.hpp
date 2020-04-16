#pragma once

#include "Renderer.hpp"
#include "Game.hpp"
#include "GUI.hpp"
#include "GUIInputMode.hpp"
#include "MainInputMode.hpp"
#include "InputManager.hpp"

#include <glm/glm.hpp>

class GUIInputMode;
class MainInputMode;

class Controller
{
private:
	Game& game;
	Renderer& renderer;
	InputManager input_manager;
	std::shared_ptr<GUIInputMode> gui_input_mode;
	std::shared_ptr<MainInputMode> main_input_mode;
	std::shared_ptr<GUI> hud, main_menu;

	int ms_per_tick;
	bool wireframe;

public:
	Controller(Game& game, Renderer& renderer);

	void StartUp();
	void OpenMainMenu();
	void CloseMainMenu();
	void Step();
	void Render();
	float GetDeltaTime()
	{
		return ms_per_tick / 1000.f;
	}
	int GetMSPerTick()
	{
		return ms_per_tick;
	}

	void Respawn();
	void GoForward();
	void StopForward();
	void GoLeftward();
	void StopLeftward();
	void GoBackward();
	void StopBackward();
	void GoRightward();
	void StopRightward();
	void ToggleWireframe();
	void TurnBy(glm::vec3 xy);
	void Jump();
	void Quit();
	void Use();
	void Punch();
};

