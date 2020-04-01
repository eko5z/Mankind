#pragma once

#include "GraphX.hpp"
#include <string>

class Shader
{
private:
	GLint shader_id;
public:
	Shader(std::string& path, GLenum type);
	~Shader();

	GLint GetShaderId() { return shader_id; }
};

