#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ECS.hpp"
#include "GraphicsComponent.hpp"
#include "TransformComponent.hpp"
#include "Camera.hpp"

#include "Mesh.hpp"
#include "Texture.hpp"
#include "Program.hpp"

#include "QuadMesh.hpp"

class GraphicsSystem: public ECS::EntitySystem
{
private:
	Camera &camera;
	std::vector<std::unique_ptr<Mesh>> meshes;
	std::vector<Texture> textures;
	std::vector<Program> programs;

	virtual void tick(ECS::World& world, float dt) override;
public:
	GraphicsSystem(Camera &camera);
};
