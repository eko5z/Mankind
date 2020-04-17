#include "GUI.hpp"

#include "tinyxml2.h"
#include "Log.hpp"
#include "GUIConstructor.hpp"

GUI::GUI(std::string xml_path) :
	root(nullptr)
{
	/* TODO: auto load from the res/fonts directory, or dynamically load, or whatever */
	fonts.emplace("DejaVuSansMono", std::make_unique<Font>("res/fonts/DejaVuSansMono.ttf", 16));

	tinyxml2::XMLDocument doc;
	doc.LoadFile(xml_path.c_str());
	LOG("Loaded XML file");

	root = std::make_shared<GUIElement>(*this);
	root->SetAttribute("font-family", "DejaVuSansMono");
	root->SetAttribute("id", "root");
	root->SetAttribute("float", "left");

	GUIConstructor gui_constructor(*this);
	doc.Accept(&gui_constructor);

	LOG("GUI successfully traversed");
}

void GUI::Draw(Program& program)
{
	/* Why? Because if we let the position be (0,0) in GL coordinates,
	   it will start at the bottom of the screen. This starts the root
	   at the top left */
	root->SetPositionPx(glm::vec2{0, 0});
	root->Draw(program);
}

