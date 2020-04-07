#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <queue>

#include "ECS.hpp"

#include "QuadMesh.hpp"
#include "RenderingInstance.hpp"
#include "GraphXManager.hpp"

class GraphicsSystem: public ECS::EntitySystem
{
private:
	GraphXManager& manager;

public:
	GraphicsSystem(GraphXManager& manager);
	virtual void tick(ECS::World& world, float dt) override;
};

