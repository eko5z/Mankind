#include "GUIElement.hpp"

#include "Log.hpp"

GUIElement::GUIElement(std::string id) :
	background(nullptr),
	foreground(nullptr),
	id(id),
	parent(*this)
{
}

GUIElement::GUIElement(std::string id, GUIElement& p) :
	background(nullptr),
	foreground(nullptr),
	id(id),
	parent(p)
{
}

void GUIElement::Draw()
{
	if (background) {
		background->Render();
	}

	if (foreground) {
		foreground->Render();
	}

	for (auto& child : children) {
		child.second->Draw();
	}
}

/* dumb depth-first search, performance shouldn't be an issue
   unless we're dealing with hyper wide hierarchies (won't happen)
   */
std::shared_ptr<GUIElement> GUIElement::GetChildByID(std::string id)
{
	if (this->id == id) {
		return std::shared_ptr<GUIElement>(this);
	}

	std::shared_ptr<GUIElement> found(nullptr);
	for (auto& child : children) {
		std::shared_ptr<GUIElement> found = child.second->GetChildByID(id);
		if (found != nullptr) {
			return found;
		}
	}
	return found;
}

