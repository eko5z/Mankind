#pragma once

#include "PhysX.hpp"

#include "glm/glm.hpp"
#include "ECS.hpp"
#include "Terrain.hpp"

class PhysicsSystem : public ECS::EntitySystem
{
private:
	bool AABBTest(glm::vec3 v, glm::vec3 box, glm::vec3 whd);
public:
	PhysicsSystem(Terrain& t) : terrain(t) {}
private:
	Terrain& terrain;
	virtual void tick(ECS::World& world, float dt) override;
};

