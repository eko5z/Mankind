#pragma once

#include "PhysX.hpp"

#include "glm/glm.hpp"
#include "ECS.hpp"
#include "World.hpp"

class PhysicsSystem : public ECS::EntitySystem
{
private:
	bool AABBTest(glm::vec3 v, glm::vec3 box, glm::vec3 whd);
public:
	PhysicsSystem(World& w) : world(w) {}
private:
	World& world;
	virtual void tick(ECS::World& world, float dt) override;
};

