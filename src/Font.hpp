#pragma once

#include <SDL2/SDL_ttf.h>

#include <string>

class Font
{
public:
	Font(std::string path, int size);
	~Font();
	TTF_Font* GetPointer()
	{
		return font_ptr;
	}
private:
	TTF_Font *font_ptr;
	int size;
};

