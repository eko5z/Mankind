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
}

void Controller::StopForward()
{
}

void Controller::GoLeftward()
{
}

void Controller::StopLeftward()
{
}

void Controller::GoBackward()
{
}

void Controller::StopBackward()
{
}

void Controller::GoRightward()
{
}

void Controller::StopRightward()
{
}

void Controller::TurnBy(glm::vec3 xy)
{
}

void Controller::Jump()
{
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

