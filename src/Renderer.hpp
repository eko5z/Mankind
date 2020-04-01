#pragma once

#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <glm/glm.hpp>
#include "GraphX.hpp"
#include "Game.hpp"
#include "Camera.hpp"
#include "Program.hpp"
#include "ChunkMesh.hpp"
#include "Texture.hpp"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void OpenWindow();
	void Render(World& world, Camera& camera);
	void AddChunk(int x, int y, int z, Chunk& c);
private:
	int view_height, view_width;
	SDL_Window* window;
	SDL_GLContext context;
	std::unique_ptr<Program> chunk_program;
	std::unique_ptr<Texture> texture;
	std::map<int, ChunkMesh> chunk_meshes;
	GLint uniform_texture;
	GLint attribute_coord;
	void UpdateVectors(glm::vec3& angle, glm::vec3& forward,
	                   glm::vec3& right, glm::vec3& lookat,
	                   glm::vec3& up);

	void DrawCrosshair();
};

