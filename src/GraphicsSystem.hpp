#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <queue>

#include "ECS.hpp"

#include "QuadMesh.hpp"
#include "RenderingInstance.hpp"
#include "GraphXManager.hpp"

class Game;

class GraphicsSystem: public ECS::EntitySystem
{
private:
	GraphXManager& manager;
	Game& game;

public:
	GraphicsSystem(Game& game, GraphXManager& manager);
	virtual void tick(ECS::World& world, float dt) override;
};

