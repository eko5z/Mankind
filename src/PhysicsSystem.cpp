#include "PhysicsSystem.hpp"

#include "TransformComponent.hpp"

void PhysicsSystem::tick(ECS::World& world, float dt)
{
	world.each<TransformComponent>(
		[&](ECS::Entity& ent,ECS::ComponentHandle<TransformComponent> transform) {
			transform->pos.y -= G_VALUE * dt;
		});
}

