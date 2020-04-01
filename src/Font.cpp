#include "Font.hpp"

#include <stdexcept>

Font::Font(std::string path, int size) :
	size(size)
{
	font_ptr = TTF_OpenFont(path.c_str(), size);
	if (font_ptr == nullptr) {
		throw std::runtime_error(TTF_GetError());
	}
}

Font::~Font()
{

}

