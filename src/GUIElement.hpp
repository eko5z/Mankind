#pragma once

#include "Mesh.hpp"
#include "FormatString.hpp"
#include <glm/glm.hpp>
#include <memory>
#include <string>
#include <map>

class GUIElement
{
protected:
	GUIElement& parent; /* self if root */
	std::unique_ptr<Mesh> background, foreground;
	std::map<std::string, std::shared_ptr<GUIElement>> children;
	std::string id;
	std::map<std::string, std::string> attributes;
	bool dirty; /* attributes have changed? */
public:
	GUIElement(std::string id);
	GUIElement(std::string id, GUIElement& parent);

	std::string GetID()
	{
		return id;
	}

	virtual void Draw();

	void AddChild(std::shared_ptr<GUIElement> e)
	{
		children.emplace(e->GetID(), e);
	}
	std::shared_ptr<GUIElement> GetChildByID(std::string id);

	void SetAttribute(std::string attribute_id, std::string fmt, ...)
	{
		va_list fmt_list;
		va_start(fmt_list, fmt);
		attributes.at(attribute_id) = FormatString::StringF(fmt, fmt_list);
		va_end(fmt_list);
		dirty = true;
	}

	std::string GetAttribute(std::string attribute_id)
	{
		return attributes.at(attribute_id);
	}

	bool IsRoot()
	{
		return this == &parent;
	}
};

