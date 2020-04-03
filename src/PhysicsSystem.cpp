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
			/* check X axis */
			if (body->vel.x != 0 and world.GetCube(floor(new_pos.x), tc->pos.y, tc->pos.z).typeID != 0) {
				new_pos.x = tc->pos.x;
				body->vel.x = 0;
			}
			if (body->vel.y != 0 and world.GetCube(tc->pos.x, floor(new_pos.y), tc->pos.z).typeID != 0) {
				new_pos.y = tc->pos.y;
				body->vel.y = 0;
			}
			if (body->vel.z != 0 and world.GetCube(tc->pos.x, tc->pos.y, floor(new_pos.z)).typeID != 0) {
				new_pos.z = tc->pos.z;
				body->vel.z = 0;
			}
			tc->pos = new_pos;
		}
	});
}

