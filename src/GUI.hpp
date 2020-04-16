#pragma once

#include <string>
#include "GUIElement.hpp"
#include "Font.hpp"

class GUI
{
public:
	GUI(std::string xml_path);
	void Draw(Program& gui_progra);
	Font& GetFont(std::string font_id)
	{
		return *fonts.at(font_id);
	}
	GUIElement* GetElementByID(std::string id)
	{
		return root->GetChildByID(id);
	}
private:
	std::shared_ptr<GUIElement> root;
	std::map<std::string, std::unique_ptr<Font>> fonts;
};

