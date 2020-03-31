#pragma once

#include <string>
#include "GraphX.hpp"

class Shader
{
private:
	int shader_id;
public:
	Shader(std::string& path, GLenum type);
	~Shader();
};

