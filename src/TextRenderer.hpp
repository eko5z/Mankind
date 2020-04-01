#pragma once

#include "Font.hpp"
#include "Program.hpp"

#include <memory>

#include <GL/gl.h>

class TextRenderer
{
public:
	TextRenderer(Font& font, const char* fmt, ...);
	~TextRenderer();
	void Draw(int x, int y);
private:
	std::unique_ptr<Program> text_program;
	TextRenderer(Font& font, const char* fmt, va_list args);
	GLuint texture_id;
	GLuint vbo;
	GLuint vao;
	GLuint ebo;
	int texture_width, texture_height;
};

