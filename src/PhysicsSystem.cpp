#include "PhysicsSystem.hpp"

#include "TransformComponent.hpp"
#include "PhysicsComponent.hpp"

#include "Log.hpp"

#include <ctime>

void PhysicsSystem::tick(ECS::World& ecs_world, float dt)
{
	struct timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	ecs_world.each<PhysicsComponent>(
	[&](ECS::Entity& ent,ECS::ComponentHandle<PhysicsComponent> body) {
		body->vel += glm::vec3(0, -G_VALUE, 0) * dt;
		if (abs(body->vel.y) > TERMINAL_VELOCITY) {
			body->vel.y = TERMINAL_VELOCITY;
		}

		auto tc = ent.get<TransformComponent>();
		if (tc.isValid()) {
			glm::vec3 new_pos = tc->pos + (body->vel * dt);
			/* check if air underneath */
			if (body->vel.y < 0 and world.GetCube(floor(new_pos.x), floor(new_pos.y), floor(new_pos.z)).typeID != 0) {
				body->vel.y = 0.;
				tc->pos = glm::vec3(new_pos.x, tc->pos.y, new_pos.z);
			} else {
				tc->pos = new_pos;
			}
		}
	});
}

