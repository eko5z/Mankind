#include "DirectionalLight.hpp"

DirectionalLight::DirectionalLight(glm::vec3 direction, glm::vec3 ambient_color, glm::vec3 diffuse_color, glm::vec3 specular_color):
	direction(direction),
	ambient_color(ambient_color),
	diffuse_color(diffuse_color),
	specular_color(specular_color)
{

}

void DirectionalLight::AddToProgram(Program &program, GLuint index)
{
	std::ostringstream direction_stream;
	direction_stream << "directional_lights[" << index << "]" << ".direction";

	std::ostringstream ambient_stream;
	ambient_stream << "directional_lights[" << index << "]" << ".ambient_color";

	std::ostringstream diffuse_stream;
	diffuse_stream << "directional_lights[" << index << "]" << ".diffuse_color";

	std::ostringstream specular_stream;
	specular_stream << "directional_lights[" << index << "]" << ".specular_color";

	program.SetVec3(direction_stream.str().c_str(), this->direction);
	program.SetVec3(ambient_stream.str().c_str(), this->ambient_color);
	program.SetVec3(diffuse_stream.str().c_str(), this->diffuse_color);
      	program.SetVec3(specular_stream.str().c_str(), this->specular_color);
}
