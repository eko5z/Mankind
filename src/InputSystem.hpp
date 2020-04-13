#pragma once

#include "ECS.hpp"

class InputSystem : public ECS::EntitySystem
{
	virtual void tick(ECS::World& world, float dt) override;
};

