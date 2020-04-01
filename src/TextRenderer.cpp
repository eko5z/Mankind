#include "TextRenderer.hpp"

TextRenderer::TextRenderer(Font& font, const char* fmt, ...)
{
	text_program = std::make_unique<Program>("res/shaders/text.vert", "res/shaders/text.frag");
	va_list args;
	va_start(args, fmt);
	TextRenderer(font, fmt, args);
	va_end(args);
}

TextRenderer::~TextRenderer()
{
	glDeleteTextures(1, &texture_id);
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
}

TextRenderer::TextRenderer(Font& font, const char* fmt, va_list args)
{
	SDL_Color color{255, 255, 255, 255};

	int string_length = snprintf(nullptr, 0, fmt, args);
	char* formatted_string = new char[string_length + 1] {0};
	snprintf(formatted_string, string_length, fmt, args);
	SDL_Surface* text_surface = TTF_RenderText_Blended(font.GetPointer(), formatted_string, color);
	texture_width = text_surface->w;
	texture_height = text_surface->h;
	delete formatted_string;

	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, text_surface->w, text_surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, text_surface->pixels);
	SDL_FreeSurface(text_surface);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	float vertices[] = {
		// positions          // colors           // texture coords
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
	};
	GLuint indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

void TextRenderer::Draw(int x, int y)
{
	text_program->Use();
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

