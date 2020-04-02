#include "MainInputManager.hpp"
#include "Log.hpp"
#include <glm/glm.hpp>

void MainInputManager::OnKeyDown(char key)
{
	Camera& c = game.GetCamera();
	glm::vec3 forward, right;
	forward.x = sinf(c.yaw);
	forward.y = 0;
	forward.z = cosf(c.yaw);

	right.x = -cosf(c.yaw);
	right.y = 0;
	right.z = sinf(c.yaw);

	switch (key) {
	case 'w':
		game.GetCamera().x += forward.x * 2;
		game.GetCamera().y += forward.y * 2;
		game.GetCamera().z += forward.z * 2;
		break;
	case 's':
		game.GetCamera().x -= forward.x * 2;
		game.GetCamera().y -= forward.y * 2;
		game.GetCamera().z -= forward.z * 2;
		break;
	case 'a':
		game.GetCamera().x -= right.x * 2;
		game.GetCamera().y -= right.y * 2;
		game.GetCamera().z -= right.z * 2;
		break;
	case 'd':
		game.GetCamera().x += right.x * 2;
		game.GetCamera().y += right.y * 2;
		game.GetCamera().z += right.z * 2;
		break;
	case 'q':
		game.GetCamera().y += 1;
		break;
	case 'e':
		game.GetCamera().y -= 1;
		break;
	}
}

void MainInputManager::OnKeyUp(char key)
{
}

void MainInputManager::OnMouseButtonDown(MouseButton button)
{
}

void MainInputManager::OnMouseButtonUp(MouseButton button)
{
}

void MainInputManager::OnMouseMotion(int x, int y, int dx, int dy)
{
	Camera& c = game.GetCamera();
	c.yaw -= dx / 500.;
	c.pitch -= dy / 500.;
}

void MainInputManager::OnQuit()
{
	game.Stop();
}

