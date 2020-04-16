#pragma once

#include <SDL2/SDL.h>
#include "GUIElement.hpp"
#include "Font.hpp"

class GUILabel : public GUIDrawer
{
public:
	using GUIDrawer::GUIDrawer;
	virtual void Draw(Program& program) override;
	virtual void Reload() override;
private:
	glm::vec2 pos;
	glm::vec2 screen_dim;
	std::shared_ptr<Texture> fg_texture;
};

