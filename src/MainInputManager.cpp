#include "MainInputManager.hpp"
#include "Log.hpp"
#include <glm/glm.hpp>

MainInputManager::MainInputManager(Game& g) :
	InputManager::InputManager(g),
	going_forward(false),
	going_backward(false),
	going_leftward(false),
	going_rightward(false),
	jumping(false)
{
}

void MainInputManager::ChangePlayerVelocity()
{
	auto player_vel = game.GetPlayerVelocity();
	Camera camera = game.GetCamera();

	float velocity_scale = 5;
	player_vel.x = 0;
	player_vel.z = 0;

	if (going_forward) {
		player_vel += camera.GetForward() * velocity_scale;
	} else if (going_backward) {
		player_vel -= camera.GetForward() * velocity_scale;
	}

	if (going_rightward) {
		player_vel += camera.GetRight() * velocity_scale;
	} else if (going_leftward) {
		player_vel -= camera.GetRight() * velocity_scale;
	}

	if (jumping) {
		player_vel.y = 5;
		jumping = false;
	}

	game.SetPlayerVelocity(player_vel);
}

void MainInputManager::OnKeyDown(char key, bool repeat)
{

	switch (key) {
	case 'w':
		going_forward = true;
		break;
	case 's':
		going_backward = true;
		break;
	case 'a':
		going_leftward = true;
		break;
	case 'd':
		going_rightward = true;
		break;
	case ' ':
		jumping = true;
		break;
	}
	ChangePlayerVelocity();
}

void MainInputManager::OnKeyUp(char key)
{
	switch (key) {
	case 'w':
		going_forward = false;
		break;
	case 's':
		going_backward = false;
		break;
	case 'a':
		going_leftward = false;
		break;
	case 'd':
		going_rightward = false;
		break;
	case 'r':
		game.SetPlayerPosition(glm::vec3(0, 100, 0));
		break;
	case ' ':
		jumping = false;
		break;
	}

	ChangePlayerVelocity();
}

void MainInputManager::OnMouseButtonDown(MouseButton button)
{
	Camera& c = game.GetCamera();

	if (button == MouseButton::LEFT) {
		game.OnPunch(c.pos, c.GetLookAt());
	} else if (button == MouseButton::RIGHT) {
		game.OnUse(c.pos, c.GetLookAt());
	}
}

void MainInputManager::OnMouseButtonUp(MouseButton button)
{
}

void MainInputManager::OnMouseMotion(int x, int y, int dx, int dy)
{
	auto rot = game.GetPlayerRotation();
	rot += glm::vec3(-dx / 500., -dy / 500., 0.);
	game.SetPlayerRotation(rot);
	ChangePlayerVelocity();
}

void MainInputManager::OnQuit()
{
	game.Stop();
}


