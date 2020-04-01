#include "MainInputManager.hpp"
#include "Log.hpp"

void MainInputManager::OnKeyDown(char key)
{
	switch (key) {
	case 'w':
		game.GetCamera().z += 1;
		break;
	case 's':
		game.GetCamera().z -= 1;
		break;
	case 'a':
		game.GetCamera().x -= 1;
		break;
	case 'd':
		game.GetCamera().x += 1;
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
	LOG(c.yaw);
	LOG(c.pitch);
}

void MainInputManager::OnQuit()
{
	game.Stop();
}

