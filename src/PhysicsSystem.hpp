#pragma once

#include "PhysX.hpp"

#include "ECS.hpp"
#include "World.hpp"

class PhysicsSystem : public ECS::EntitySystem
{
public:
	PhysicsSystem(World& w) : world(w) {}
	private:
	World& world;
	virtual void tick(ECS::World& world, float dt) override;
};

