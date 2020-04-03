#pragma once

#include "PhysX.hpp"

#include "ECS.hpp"

class PhysicsSystem : public ECS::EntitySystem
{
	virtual void tick(ECS::World& world, float dt) override;
};

