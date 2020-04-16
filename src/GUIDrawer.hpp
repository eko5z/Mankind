#pragma once

#include <memory>

#include "Mesh.hpp"

class GUIElement;

class GUIDrawer
{
protected:
	GUIElement& element;
	std::unique_ptr<Mesh> background, foreground;
public:
	GUIDrawer(GUIElement& element) : element(element) {}
	virtual void Draw(Program& program);
	virtual void Reload() = 0;
};

