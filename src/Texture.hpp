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
public:
	void Bind()
	{
		glBindTexture(GL_TEXTURE_2D, texture_id);
	}
	GLuint texture_id;

	Texture(std::string path);
	~Texture();
};

