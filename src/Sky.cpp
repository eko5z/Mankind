#include "Sky.hpp"

#include "Log.hpp"

//   2---4
//   |\  |
//   | \ |
//   |  \|
//   1___3

/// Generate the fullscreen quad.


#define v1 glm::vec3{-1.0, -1.0, 0.0}
#define v2 glm::vec3{-1.0, 1.0, 0.0}
#define v3 glm::vec3{1.0, -1.0, 0.0}
#define v4 glm::vec3{1.0, 1.0, 0.0}

#define u1 glm::vec2{0, 0}
#define u2 glm::vec2{0, 1}
#define u3 glm::vec2{1, 0}
#define u4 glm::vec2{1, 1}

Sky::Sky():
	Mesh::Mesh(
		std::vector<glm::vec3>{v1, v2, v3, v3, v2, v4},
		std::vector<glm::vec3>(),
	    std::vector<glm::vec2>{u1, u2, u3, u2, u4, u3},
		std::vector<GLuint>{0, 1, 2, 3, 4, 5},
	    nullptr, nullptr
	)
{
	LOG("In sky constructor");
}

void Sky::Render()
{
	glDisable(GL_DEPTH_TEST);
	Mesh::Render();
	glEnable(GL_DEPTH_TEST);
}
