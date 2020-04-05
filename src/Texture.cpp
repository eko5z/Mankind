#include "Texture.hpp"

#include "Log.hpp"

#include <iostream>

Texture::Texture(std::string path) :
	res(IMG_Load(path.c_str()))
{
	if (res == nullptr) {
		throw std::runtime_error(SDL_GetError());
	}

	Load();
	SDL_FreeSurface(res);
}

Texture::Texture(SDL_Surface* s) :
	res(s)
{
	Load();
}

void Texture::Load()
{
	glGenTextures(1, &this->texture_id);
	glBindTexture(GL_TEXTURE_2D, this->texture_id);
	GLuint pixel_format;
	if (res->format->BytesPerPixel == 3) {
		pixel_format = GL_RGB;
	} else if (res->format->BytesPerPixel == 4) {
		pixel_format = GL_RGBA;
	}
	glTexImage2D(
	    GL_TEXTURE_2D, 0, pixel_format, res->w, res->h,
	    0, pixel_format, GL_UNSIGNED_BYTE, res->pixels
	);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	float color[] = {1.0f, 0.f, 0.f, 11.f};
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);
	glGenerateMipmap(GL_TEXTURE_2D);
}

Texture::~Texture()
{
	glDeleteTextures(1, &texture_id);
}

