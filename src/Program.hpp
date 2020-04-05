#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

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

	void SetMat4(const char *name, glm::mat4 value)
	{
		glUniformMatrix4fv(this->GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
	}

	void SetVec3(const char *name, glm::vec3 value)
	{
		glUniform3f(this->GetUniformLocation(name), value.x, value.y, value.z);
	}

	void SetVec2(const char *name, glm::vec2 value)
	{
		glUniform2f(this->GetUniformLocation(name), value.x, value.y);
	}

	void SetFloat(const char *name, float value)
	{
		glUniform1f(this->GetUniformLocation(name), value);
	}
};

