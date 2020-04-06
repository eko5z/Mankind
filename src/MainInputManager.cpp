#include "MainInputManager.hpp"
#include "Log.hpp"
#include <glm/glm.hpp>

MainInputManager::MainInputManager(Game& g) :
	InputManager::InputManager(g),
	going_forward(false),
	going_backward(false),
	going_leftward(false),
	going_rightward(false),
	jumping(false),
	wireframe(false)
{
}

void MainInputManager::ChangePlayerVelocity()
{
	auto player_vel = game.GetPlayerVelocity();
	auto player_rot = game.GetPlayerRotation();
	glm::vec3 forward, right;
	forward.x = sinf(player_rot.x);
	forward.y = 0;
	forward.z = cosf(player_rot.x);

	right.x = -cosf(player_rot.x);
	right.y = 0;
	right.z = sinf(player_rot.x);

	forward = glm::normalize(forward);
	right = glm::normalize(right);
	float velocity_scale = 5;
	player_vel.x = 0;
	player_vel.z = 0;
	if (going_forward) {
		player_vel.x += forward.x * velocity_scale;
		player_vel.z += forward.z * velocity_scale;
	} else if (going_backward) {
		player_vel.x -= forward.x * velocity_scale;
		player_vel.z -= forward.z * velocity_scale;
	}

	if (going_rightward) {
		player_vel.x += right.x * velocity_scale;
		player_vel.z += right.z * velocity_scale;
	} else if (going_leftward) {
		player_vel.x -= right.x * velocity_scale;
		player_vel.z -= right.z * velocity_scale;
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
	case 'p':
		this->wireframe = !this->wireframe;
		if(this->wireframe) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			this->wireframe = !this->wireframe;
		} else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			this->wireframe = !this->wireframe;
		}
		break;
	}
	ChangePlayerVelocity();
}

void MainInputManager::OnKeyUp(char key)
{
	auto player_vel = game.GetPlayerVelocity();
	auto player_rot = game.GetPlayerRotation();
	glm::vec3 forward, right;
	forward.x = sinf(player_rot.x);
	forward.y = 0;
	forward.z = cosf(player_rot.y);

	right.x = -cosf(player_rot.x);
	right.y = 0;
	right.z = sinf(player_rot.x);

	forward = glm::normalize(forward);
	right = glm::normalize(right);

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
	glm::vec3 position(c.x, c.y, c.z);
	glm::vec3 lookat( sinf(c.yaw) * cosf(c.pitch),
	                  sinf(c.pitch),
	                  cosf(c.yaw) * cosf(c.pitch));

	if (button == MouseButton::LEFT) {
		game.OnPunch(position, lookat);
	} else if (button == MouseButton::RIGHT) {
		game.OnUse(position, lookat);
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


