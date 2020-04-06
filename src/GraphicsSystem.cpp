#include "GraphicsSystem.hpp"

GraphicsSystem::GraphicsSystem(World &w):
	world(w)
{
	// Add a quad mesh.
	// this->meshes.push_back(std::make_unique<QuadMesh>());

	// Add the tree texture.
	// this->textures.push_back(Texture("res/tex/tree.png"));

	// Add the billboard program.
	// this->programs.push_back(Program("res/shaders/billboard.vert", "res/shaders/billboard.frag"));
}

void GraphicsSystem::tick(ECS::World& ecs_world, float dt)
{
	ecs_world.each<GraphicsComponent>(
	[&](ECS::Entity& ent, ECS::ComponentHandle<GraphicsComponent> gc) {
		// First, use the program.
		this->programs[gc->program_id].Use();

		// Then, bind and activate the textures.
		glActiveTexture(GL_TEXTURE0);
		this->textures[gc->diffuse_id].Bind();
		glActiveTexture(GL_TEXTURE1);
		this->textures[gc->specular_id].Bind();

		// Finally, render the mesh.
		this->meshes[gc->mesh_id]->Render();
	});
}
