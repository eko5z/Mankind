#include "BaseGUIElement.hpp"

#include "Log.hpp"

BaseGUIElement::BaseGUIElement(std::string id) :
	background(nullptr),
	foreground(nullptr),
	id(id)
{
}

void BaseGUIElement::Draw()
{
	if (background) {
		background->Render();
	}

	if (foreground) {
		foreground->Render();
	}

	for (auto& child : children) {
		child->Draw();
	}
}

