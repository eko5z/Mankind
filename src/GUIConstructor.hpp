#pragma once

#include <tinyxml2.h>

class GUI;

class GUIConstructor : public tinyxml2::XMLVisitor
{
	/* elements will be added to the root */
	GUI& gui;
public:
	GUIConstructor(GUI& gui);
	virtual bool VisitEnter(const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* attrib);
};

