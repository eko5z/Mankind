#include "Controller.hpp"


Controller::Controller(Game& game, Renderer& renderer) :
	game(game), 
	renderer(renderer),
	ms_per_tick(25),
	main_input_mode(std::make_shared<MainInputMode>(*this)),
	gui_input_mode(std::make_shared<GUIInputMode>(*this))
{

	input_manager.SetInputMode(main_input_mode);
}

void Controller::StartUp()
{
	game.Start(0);
	LOG("Game started");
}

void Controller::OpenMainMenu()
{
	input_manager.SetInputMode(gui_input_mode);
}

void Controller::CloseMainMenu()
{
	input_manager.SetInputMode(main_input_mode);
}

void Controller::Step()
{
	input_manager.ProcessEvents();
	game.Update(GetDeltaTime());
}

void Controller::Render()
{
	renderer.Render();
}

void Controller::ToggleWireframe()
{
	if(this->wireframe) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		this->wireframe = !this->wireframe;
	} else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		this->wireframe = !this->wireframe;
	}
}

void Controller::Respawn()
{
}

void Controller::GoForward()
{
	game.GetPlayerInputComponent()->go_forward = true;
}

void Controller::StopForward()
{
	game.GetPlayerInputComponent()->go_forward = false;
}

void Controller::GoLeftward()
{
	game.GetPlayerInputComponent()->go_leftward = true;
}

void Controller::StopLeftward()
{
	game.GetPlayerInputComponent()->go_leftward = false;
}

void Controller::GoBackward()
{
	game.GetPlayerInputComponent()->go_backward = true;
}

void Controller::StopBackward()
{
	game.GetPlayerInputComponent()->go_backward = false;
}

void Controller::GoRightward()
{
	game.GetPlayerInputComponent()->go_rightward = true;
}

void Controller::StopRightward()
{
	game.GetPlayerInputComponent()->go_rightward = false;
}

void Controller::TurnBy(glm::vec3 xy)
{
	auto player_rotation = game.GetPlayerRotation();
	player_rotation += xy;
	player_rotation.z = std::max(std::min(3.14592f/2.f, player_rotation.z), -3.141592f / 2.f);
	game.SetPlayerRotation(player_rotation);
}

void Controller::Jump()
{
	game.GetPlayerInputComponent()->jump = true;
}

void Controller::Quit()
{
	game.Stop();
}

void Controller::Use()
{
}

void Controller::Punch()
{
}

