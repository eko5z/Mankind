#pragma once

#include <SDL2/SDL.h>
#include "BaseGUIElement.hpp"
#include "Font.hpp"

class GUILabel : public BaseGUIElement
{
public:
	GUILabel(std::string id, std::shared_ptr<Font> font, std::string fmt, ...);
	void SetText(std::string fmt, ...);
	void SetFont(std::shared_ptr<Font> font);
	void SetForegroundColor(SDL_Color new_color);
	virtual void Draw() override;
private:
	bool dirty;
	std::string text;
	std::shared_ptr<Font> font;
	void Reload();
	void SetText(std::string fmt, va_list vl);
	SDL_Color fg_color;
};

