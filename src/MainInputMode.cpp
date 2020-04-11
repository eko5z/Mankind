#include "MainInputMode.hpp"
#include "Log.hpp"
#include <glm/glm.hpp>
#include "Controller.hpp"

void MainInputMode::OnKeyDown(char key, bool repeat)
{

	switch (key) {
	case 'w':
		controller.GoForward();
		break;
	case 's':
		controller.GoBackward();
		break;
	case 'a':
		controller.GoLeftward();
		break;
	case 'd':
		controller.GoRightward();
		break;
	case ' ':
		controller.Jump();
		break;
	case 'p':
		controller.ToggleWireframe();
		break;
	}
}

void MainInputMode::OnKeyUp(char key)
{
	switch (key) {
	case 'w':
		controller.StopForward();
		break;
	case 's':
		controller.StopBackward();
		break;
	case 'a':
		controller.StopLeftward();
		break;
	case 'd':
		controller.StopRightward();
		break;
	case 'r':
		controller.Respawn();
		break;
	case ' ':
		break;

	case '\033':
		controller.OpenMainMenu();
		break;
	}
}

void MainInputMode::OnMouseButtonDown(MouseButton button)
{
	if (button == MouseButton::LEFT) {
		controller.Punch();
	} else if (button == MouseButton::RIGHT) {
		controller.Use();
	}
}

void MainInputMode::OnMouseButtonUp(MouseButton button)
{
}

void MainInputMode::OnMouseMotion(int x, int y, int dx, int dy)
{
	controller.TurnBy(glm::vec3(-dx / 500., -dy / 500., 0.));
}

void MainInputMode::OnQuit()
{
	controller.Quit();
}


