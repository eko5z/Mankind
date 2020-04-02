#pragma once

#include <glm/glm.hpp>

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
	void Use()
	{
		glUseProgram(program_id);
	}

	GLuint GetUniformLocation(const char* name)
	{
		return glGetUniformLocation(program_id, name);
	}

  void SetVec3(const char *name, glm::vec3 vector)
  {
    glUniform3f(this->GetUniform(name), vector.x, vector.y, vector.z);
  }
};

