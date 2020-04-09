#include "GraphicsSystem.hpp"

#include "GraphicsComponent.hpp"
#include "TransformComponent.hpp"

#include "Log.hpp"

#include "Game.hpp"

#include "glm/gtx/vector_angle.hpp"

GraphicsSystem::GraphicsSystem(Game& game, GraphXManager& manager) :
	game(game),
	manager(manager)
{
}

void GraphicsSystem::tick(ECS::World& ecs_world, float dt)
{
	manager.ResetRenderingInstances();
	ecs_world.each<GraphicsComponent>(
	[&](ECS::Entity& ent, ECS::ComponentHandle<GraphicsComponent> gc) {
		if(ent.has<TransformComponent>()) {
			// Get the transform component.
			auto transform = ent.get<TransformComponent>();

			/* Cull entities not within 90 degrees of our lookAt
			 */
			glm::vec3 clookat = game.GetCamera().GetLookAt();
			glm::vec3 toEnt = glm::normalize(transform->position - game.GetCamera().position);
			float angle = glm::orientedAngle(clookat, toEnt, glm::vec3(0, 1, 0));
			if (fabs(angle) > 3.14159 / 2) {
				return;
			}

			// TODO: figure out how glm::rotate gets an angle and shit?
			glm::mat4 model = glm::mat4();
			model = glm::translate(model, transform->position);
			model = glm::scale(model, transform->scale);
			model = glm::rotate(model, transform->rotation.x, glm::vec3{1.0, 0.0, 0.0});
			model = glm::rotate(model, transform->rotation.y, glm::vec3{0.0, 1.0, 0.0});
			model = glm::rotate(model, transform->rotation.z, glm::vec3{0.0, 0.0, 1.0});

			RenderingInstance ri;
			ri.model_matrix = model;
			ri.meshID = gc->meshID;
			ri.textureID[0] = gc->textureID[0];
			ri.textureID[1] = gc->textureID[1];
			ri.textureID[2] = gc->textureID[2];
			ri.textureID[3] = gc->textureID[3];
			ri.programID = gc->programID;
			manager.AddRenderingInstance(ri);
		}
	});
}

