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
#include "Font.hpp"
#include "TextRenderer.hpp"

#include "Mesh.hpp"

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
	void UpdateVectors(glm::vec3& angle, glm::vec3& forward,
	                   glm::vec3& right, glm::vec3& lookat,
	                   glm::vec3& up);
  std::unique_ptr<Program> default_program;
  std::map<int, ChunkMesh> chunk_meshes;
};

