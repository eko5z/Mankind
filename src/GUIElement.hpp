#pragma once

#include "FormatString.hpp"
#include "GUIDrawer.hpp"

#include <glm/glm.hpp>
#include <memory>
#include <string>
#include <map>
#include <tinyxml2.h>
#include <iostream>

class GUI;

class GUIElement
{
	GUIElement& parent; /* self if root */

	/* TODO: the map should be used for lookups, and a vector
	should be used to keep the insertion order */
	std::map<std::string, std::shared_ptr<GUIElement>> children;
	std::map<std::string, std::string> attributes;
	bool dirty; /* have attributes changed? */

	glm::vec2 screen_size; /* size of the screen in pixels */

	glm::vec2 dimensions; /* size, in the range 0..1 */
	glm::vec2 position; /* position of the upper-left corner, in the range 0..1 */

	/* TODO: should really be special children,
	as in the case, for instance, of <p>Lorem <a ...> ipsum </a> sit amet</p>,
	where there would be two different instances of text drawn, with the child in
	in between. */
	std::string text;
	std::unique_ptr<GUIDrawer> drawer;

	GUI& gui;

	glm::vec2 Pixel2GL(glm::vec2 px)
	{
		screen_size = GetScreenSizePx();
		return glm::vec2{(float) px.x / screen_size.x * 2.f, (float)px.y / screen_size.y * 2.f};
	}

	glm::vec2 PixelPos2GL(glm::vec2 px)
	{
		screen_size = GetScreenSizePx();
		return glm::vec2{(float) px.x / screen_size.x * 2.f, 2. - ((float)px.y / screen_size.y * 2.f)};
	}


public:
	GUIElement(GUI& gui);
	GUIElement(GUI& gui, GUIElement& parent);

	GUI& GetGUI()
	{
		return gui;
	}

	glm::vec2 GetScreenSizePx()
	{
		if (not IsRoot()) {
			return parent.GetScreenSizePx();
		} else {
			return screen_size;
		}
	}

	void SetScreenSizePx(glm::vec2 size)
	{
		screen_size = size;
	}

	std::string GetID()
	{
		return attributes.at("id");
	}

	virtual void Draw(Program& program);

	glm::vec2 GetSizePx()
	{
		screen_size = GetScreenSizePx();
		return glm::vec2{dimensions.x * screen_size.x, dimensions.y * screen_size.y};
	}

	void SetSizePx(glm::vec2 size)
	{
		dimensions = Pixel2GL(size);
	}

	void SetSize(glm::vec2 size)
	{
		dimensions = size;
	}

	glm::vec2 GetSize()
	{
		return dimensions;
	}

	void SetPosition(glm::vec2 pos)
	{
		position = pos;
	}

	void SetPositionPx(glm::vec2 px)
	{
		position = PixelPos2GL(px);
	}

	void AddChild(std::shared_ptr<GUIElement> e)
	{
		children.emplace(e->GetID(), e);
	}

	void SetAttribute(std::string attribute_id, std::string fmt, ...)
	{
		va_list fmt_list;
		va_start(fmt_list, fmt);
		attributes[attribute_id] = FormatString::StringF(fmt, fmt_list);
		va_end(fmt_list);
		dirty = true;
	}

	void SetDrawer(std::unique_ptr<GUIDrawer> drawer)
	{
		this->drawer = std::move(drawer);
	}

	void SetText(std::string s)
	{
		text = s;
		dirty = true;
	}
	std::string GetText()
	{
		return text;
	}

	/*!
		Attributes are inherited, so if this node does not define it,
		its value will be taken from its parent. Throws an exception
		if the attribute could not be found in the hierarchy.
	 */
	std::string GetAttribute(std::string attribute_id)
	{
		if (attributes.find(attribute_id) == std::end(attributes) and not IsRoot()) {
			return parent.GetAttribute(attribute_id);
		} else {
			return attributes.at(attribute_id);
		}
	}

	bool IsRoot()
	{
		return this == &parent;
	}

	GUIElement* GetRoot();
	GUIElement* GetChildByID(std::string id);

};

