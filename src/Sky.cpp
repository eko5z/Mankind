#include "Sky.hpp"

Sky::Sky():
	QuadMesh::QuadMesh(nullptr, nullptr)
{

}

void Sky::Render()
{
	glDisable(GL_DEPTH_TEST);
	QuadMesh::Render();
	glEnable(GL_DEPTH_TEST);
}
