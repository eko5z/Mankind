#pragma once

#include <string>
#include <stdexcept>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "GraphX.hpp"

class Texture
{
private:
	SDL_Surface* res;
	GLuint texture_id, program_id;
	GLint uniform;
public:
	Texture(std::string& path);
	~Texture();
};

