#include "GUIInputMode.hpp"
#include "Controller.hpp"

void GUIInputMode::OnKeyDown(char key, bool repeat)
{
}

void GUIInputMode::OnKeyUp(char key)
{
	/* escape key */
	if (key == '\033') {
		controller.CloseMainMenu();	
	}
}

void GUIInputMode::OnMouseButtonDown(MouseButton button)
{
}

void GUIInputMode::OnMouseButtonUp(MouseButton button)
{
}

void GUIInputMode::OnMouseMotion(int x, int y, int dx, int dy)
{
}

void GUIInputMode::OnQuit()
{
	controller.Quit();
}

