#include "Program.hpp"

#include <stdexcept>
#include "Log.hpp"

Program::Program(std::string vshader_path, std::string fshader_path) :
	f_shader(fshader_path, GL_FRAGMENT_SHADER),
	v_shader(vshader_path, GL_VERTEX_SHADER)
{
	LOG("Creating program");
	program_id = glCreateProgram();

	glAttachShader(program_id, v_shader.GetShaderId());
	glAttachShader(program_id, f_shader.GetShaderId());

	// Binding attribute locations to the program.
	glBindAttribLocation(program_id, 0, "position");
	glBindAttribLocation(program_id, 1, "normal");
	glBindAttribLocation(program_id, 2, "uv");

	glUniform1i(GetUniformLocation("texture_1"), 0);

	LOG("Linking program");

	glLinkProgram(program_id);
	GLint link_ok = GL_FALSE;
	glGetProgramiv(program_id, GL_LINK_STATUS, &link_ok);

	if (!link_ok) {
		GLint maxLength(0);
		glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &maxLength);

		std::string errorLog(maxLength, '\0');
		glGetProgramInfoLog(program_id, maxLength, &maxLength, &errorLog[0]);

		throw std::runtime_error(errorLog);
	}

}

Program::~Program()
{
	glDeleteProgram(program_id);
}

GLint Program::GetAttrib(const char* name)
{
	GLint attribute = glGetAttribLocation(program_id, name);
	if (attribute == -1) {
		LOG("ERROR: could not find attribute");
	}
	return attribute;
}

GLint Program::GetUniform(const char* name)
{
	GLint uniform = glGetUniformLocation(program_id, name);
	if (uniform == -1) {
		LOG("ERROR: could not find uniform");
	}
	return uniform;
}

