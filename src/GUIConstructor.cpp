#include "GUIConstructor.hpp"

#include "GUI.hpp"
#include "GUILabel.hpp"
#include <iostream>


GUIConstructor::GUIConstructor(GUI& gui) :
	gui(gui)
{
}

bool GUIConstructor::VisitEnter(const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* attrib)
{
	std::string elm_type(element.Name());
	auto *parent = element.Parent()->ToElement();


	/* we're not on the root element*/
	if (parent != nullptr) {
		auto parent_id = parent->Attribute("id");
		auto parent_element = gui.GetElementByID(parent_id);
		if (parent_element == nullptr) {
			throw std::runtime_error("Parent element is null!");
		}
		std::unique_ptr<GUIElement> gui_element = std::make_unique<GUIElement>(gui, *parent_element);

		if (elm_type == "label") {
			gui_element->SetDrawer(std::make_unique<GUILabel>(*gui_element));
		} else if (elm_type == "div") {
			gui_element->SetDrawer(nullptr);
		} else {
			throw std::runtime_error("Uknown GUI element type '"+elm_type+"'");
		}
		gui_element->SetText(element.GetText());
		gui_element->SetPositionPx(glm::vec2{0, 0});

		while (attrib) {
			gui_element->SetAttribute(attrib->Name(), attrib->Value());
			attrib = attrib->Next();
		}

		parent_element->AddChild(std::move(gui_element));
	}

	return true;
}

