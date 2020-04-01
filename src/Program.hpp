#pragma once

#include "Shader.hpp"

class Program
{
private:
	GLint program_id;
	Shader v_shader;
	Shader f_shader;
public:
	Program(std::string vshader_path, std::string fshader_path);
	~Program();
	GLint GetAttrib(const char* name);
	GLint GetUniform(const char* name);
	void Use() { glUseProgram(program_id); }
};

