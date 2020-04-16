#include "GUIDrawer.hpp"

#include "GUIElement.hpp"

void GUIDrawer::Draw(Program& program)
{
	if (background) {
		background->Render();
	}

	if (foreground) {
		foreground->Render();
	}
}

