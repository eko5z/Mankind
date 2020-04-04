#pragma once

#include "Mesh.hpp"
#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include <string>

class BaseGUIElement
{
protected:
	std::unique_ptr<Mesh> background, foreground;
	std::vector<std::shared_ptr<BaseGUIElement>> children;
	std::string id;
public:
	BaseGUIElement(std::string id);

	virtual void Draw();
	void AddChild(std::shared_ptr<BaseGUIElement> e) { children.push_back(std::move(e)); }
};

