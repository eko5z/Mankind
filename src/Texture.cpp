#include "Texture.hpp"

Texture::Texture(std::string& path) :
	res(IMG_Load(path.c_str()))
{
	if (res == nullptr) {
		throw std::runtime_error(SDL_GetError());
	}
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,
	             0,
	             GL_RGBA,
	             res->w,
	             res->h,
	             0,
	             GL_RGBA,
	             GL_UNSIGNED_BYTE,
	             res->pixels);
	SDL_FreeSurface(res);
}

Texture::~Texture()
{
	glDeleteTextures(1, &texture_id);
}

