#include "Shader.hpp"

#include <SDL2/SDL_opengl.h>
#include <fstream>

Shader::Shader(std::string& path, GLenum type)
{
	shader_id = glCreateShader(type);
	std::ifstream source_file;
	source_file.open(path);
	std::string s((std::istreambuf_iterator<char>(source_file)),
		std::istreambuf_iterator<char>());
	const char* source = s.c_str();
	source_file.close();

	glShaderSource(shader_id, 1, &source, NULL);
}

Shader::~Shader()
{
}

