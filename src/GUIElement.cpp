#include "GUIElement.hpp"

#include "Log.hpp"

GUIElement::GUIElement(GUI& gui) :
	parent(*this),
	gui(gui),
	drawer(nullptr)
{
}

GUIElement::GUIElement(GUI& gui, GUIElement& p) :
	parent(p),
	gui(gui),
	drawer(nullptr)
{
}

void GUIElement::Draw(Program& program)
{
	program.SetVec2("element_offset", position);
	if (drawer) {
		if (dirty) {
			drawer->Reload();
			dirty = false;
		}
		drawer->Draw(program);
	}
	glm::vec2 current_offset(position);
	for (auto& child : children) {
		child.second->SetPosition(current_offset);
		child.second->Draw(program);
		/* we must go in reverse because of pixel positions */
		current_offset.y -= child.second->GetSize().y;
	}
}

/* dumb depth-first search, performance shouldn't be an issue
   unless we're dealing with very large hierarchies
   (hopefully won't happen)
   */
GUIElement* GUIElement::GetChildByID(std::string id)
{
	if (GetID() == id) {
		return this;
	}

	GUIElement* found(nullptr);
	for (auto& child : children) {
		found = child.second->GetChildByID(id);
		if (found != nullptr) {
			return found;
		}
	}
	return found;
}

GUIElement* GUIElement::GetRoot()
{
	return this->IsRoot() ? this : parent.GetRoot();
}

