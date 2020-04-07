#include "GraphicsSystem.hpp"

GraphicsSystem::GraphicsSystem(Camera &camera):
	camera(camera)
{
	// Add a quad mesh.
	this->meshes.push_back(std::make_unique<QuadMesh>(nullptr, nullptr));

	// Add the tree texture.
	this->textures.push_back(Texture("res/tex/tree.png"));

	// Add the billboard program.
	this->programs.push_back(Program("res/shaders/billboard.vert", "res/shaders/billboard.frag"));
}

void GraphicsSystem::tick(ECS::World& ecs_world, float dt)
{
	ecs_world.each<GraphicsComponent>(
	[&](ECS::Entity& ent, ECS::ComponentHandle<GraphicsComponent> gc) {
		// First, use the program.
		this->programs[gc->program_id].Use();

		// Calculate the view and projection matrix.
		float h_fov = 90.f;
		// This doesn't use the functions in MathematX.hpp,
		// because the linker fucking breaks everything.
		float v_fov_rad = 2.0f * atan(tan((h_fov * 4.0 * atan(1.0) / 180.0) * 0.5f) /
		                              (float)this->camera.view_width /
		                              (float)this->camera.view_height);

		glm::mat4 view = glm::lookAt(this->camera.position, this->camera.position + this->camera.GetLookAt(), this->camera.GetUp());
		glm::mat4 projection = glm::scale(
		                           glm::perspective(v_fov_rad, 1.0f*this->camera.view_width/this->camera.view_height, 0.01f, 1000.0f), glm::vec3(0.5f, 0.5f, 0.5f));

		// I have no idea how to fix this right now, but if
		// the shader has no model, view, projection, then
		// this will crash.
		if(ent.has<TransformComponent>()) {
			// Get the transform component.
			auto transform = ent.get<TransformComponent>();

			// Generate the model matrix.
			glm::mat4 translate = glm::translate(glm::mat4(), transform->position);
			// The angle obviously isn't 3.14f, I don't really
			// care to search it online so let it be.
			glm::mat4 rotate = glm::rotate(translate, 3.14f, transform->rotation);
			glm::mat4 model = glm::scale(rotate, transform->scale);

			this->programs[gc->program_id].SetMat4("model", model);
			this->programs[gc->program_id].SetMat4("view", view);
			this->programs[gc->program_id].SetMat4("projection", projection);
			this->programs[gc->program_id].SetVec3("camera_position", this->camera.position);
			this->programs[gc->program_id].SetVec3("camera_lookat", this->camera.GetLookAt());
		}

		// Then, bind and activate the textures.
		glActiveTexture(GL_TEXTURE0);
		this->textures[gc->diffuse_id].Bind();
		glActiveTexture(GL_TEXTURE1);
		this->textures[gc->specular_id].Bind();

		// Finally, render the mesh.
		this->meshes[gc->mesh_id]->Render();
	});
}
