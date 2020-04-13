#pragma once

#include <SDL2/SDL.h>
#include "GUIElement.hpp"
#include "Font.hpp"

class GUILabel : public GUIElement
{
public:
	GUILabel(GUIElement& parent, std::string id, glm::vec2 pos, glm::vec2 screen_dim,
	         std::shared_ptr<Font> font, std::string fmt, ...);
	void SetFont(std::shared_ptr<Font> font);
	void SetForegroundColor(SDL_Color new_color);
	virtual void Draw() override;
private:
	glm::vec2 pos;
	glm::vec2 screen_dim;
	std::shared_ptr<Font> font;
	void Reload();
	SDL_Color fg_color;
	std::shared_ptr<Texture> fg_texture;
};

