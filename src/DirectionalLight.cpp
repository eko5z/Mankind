#include "DirectionalLight.hpp"

DirectionalLight::DirectionalLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular):
  direction(direction),
  ambient(ambient),
  diffuse(diffuse),
  specular(specular)
{

}

void DirectionalLight::AddToProgram(Program &program, GLuint index)
{
  std::ostringstream direction_stream;
  direction_stream << "directional_lights[" << index << "]" << ".direction";

  std::ostringstream ambient_stream;
  ambient_stream << "directional_lights[" << index << "]" << ".ambient";

  std::ostringstream diffuse_stream;
  diffuse_stream << "directional_lights[" << index << "]" << ".diffuse";
  
  std::ostringstream specular_stream;
  specular_stream << "directional_lights[" << index << "]" << ".specular";
  
  program.SetVec3(direction_stream.str().c_str(), this->direction);
  program.SetVec3(ambient_stream.str().c_str(), this->ambient);
  program.SetVec3(diffuse_stream.str().c_str(), this->diffuse);
  program.SetVec3(specular_stream.str().c_str(), this->specular);
}
