#include "Shader.hpp"

#include <fstream>
#include <sstream>

#include "Log.hpp"

Shader::Shader(std::string& path, GLenum type)
{
	LOG(path);
	shader_id = glCreateShader(type);
	std::ifstream source_file(path);
	if (not source_file.is_open()) {
		throw std::runtime_error("Could not open source file");
	}
	std::stringstream buffer;
	buffer << source_file.rdbuf();
	std::string src = buffer.str();
	const char* source = src.c_str();
	source_file.close();

	glShaderSource(shader_id, 1, &source, NULL);

	GLint compile_ok = GL_FALSE;
	glCompileShader(shader_id);
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compile_ok);
	if (compile_ok == GL_FALSE) {
		GLint maxLength(0);
		glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &maxLength);
		std::string errorLog(maxLength, '\0');
		glGetShaderInfoLog(shader_id, maxLength, &maxLength, &errorLog[0]);
		throw std::runtime_error(errorLog);
	}
}

Shader::~Shader()
{
	glDeleteShader(shader_id);
}

