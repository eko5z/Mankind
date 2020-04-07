#pragma once

struct GraphicsComponent {
	int mesh_id;
	int diffuse_id, specular_id;
	int program_id;

	GraphicsComponent(int mesh_id, int diffuse_id, int specular_id, int program_id):
		mesh_id(mesh_id), diffuse_id(diffuse_id), specular_id(specular_id),
		program_id(program_id) {}
};

