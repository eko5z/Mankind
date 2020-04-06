#pragma once

#include "ECS.hpp"
#include "World.hpp"
#include "GraphicsComponent.hpp"

#include "Mesh.hpp"
#include "Texture.hpp"
#include "Program.hpp"

#include "QuadMesh.hpp"

class GraphicsSystem: public ECS::EntitySystem
{
private:
	World &world;
	std::vector<std::unique_ptr<Mesh>> meshes;
	std::vector<Texture> textures;
	std::vector<Program> programs;

	virtual void tick(ECS::World& world, float dt) override;
public:
	GraphicsSystem(World &w);
};
