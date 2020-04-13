#include "InputSystem.hpp"
#include "InputComponent.hpp"
#include "PhysicsComponent.hpp"
#include "TransformComponent.hpp"
#include "PhysX.hpp"

#include "Log.hpp"

void InputSystem::tick(ECS::World& ecs_world, float dt)
{
	ecs_world.each<InputComponent>(
	[&](ECS::Entity& ent,ECS::ComponentHandle<InputComponent> input) {
		auto pc = ent.get<PhysicsComponent>();
		auto tc = ent.get<TransformComponent>();
		if (not tc.isValid() or not pc.isValid()) {
			throw std::runtime_error("Attempted to assign an InputComponent to an entity lacking a PhysicsComponent or a TransformComponent.");
		}

		/* Movement in a 2D plane
		   For 3D movement (as in when flying), we would get a lookat vector
		   instead of forward.
		*/
		glm::vec3 forward = glm::normalize(glm::vec3 {
			sinf(tc->rotation.x),
			0.f,
			cosf(tc->rotation.x)
		});
		glm::vec3 up = glm::vec3(0.f, 1.f, 0.f);
		glm::vec3 right = glm::normalize(glm::cross(forward, up));

		glm::vec3 new_vel{0.f, 0.f, 0.f};

		if (input->go_forward) {
			new_vel += forward;
		}
		if (input->go_backward) {
			new_vel -= forward;
		}
		if (input->go_rightward) {
			new_vel += right;
		}
		if (input->go_leftward) {
			new_vel -= right;
		}

		if (new_vel.x != 0 and new_vel.y != 0 and new_vel.z != 0) {
			new_vel = glm::normalize(new_vel);
		}
		pc->vel = (new_vel * 5.f) + glm::vec3(0.f, pc->vel.y, 0.f);

		if (input->jump) {
			input->jump = false;
			pc->vel.y = G_VALUE;
		}

	});
}

