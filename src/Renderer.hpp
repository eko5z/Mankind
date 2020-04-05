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
#include "GUILabel.hpp"

#include "Mesh.hpp"
#include "DirectionalLight.hpp"
#include "Sky.hpp"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void OpenWindow();
	void Render(World& world, Camera& camera);
	void AddChunk(World& w, int x, int y, int z, Chunk& c);
private:
	float h_fov, v_fov_rad;
	void DrawSky(Camera& camera);
	void LoadChunks(World& world, Camera& camera);
	std::shared_ptr<Font> main_font;
	std::unique_ptr<GUILabel> position_label, version_label;
	int view_height, view_width;
	SDL_Window* window;
	SDL_GLContext context;
	void UpdateVectors(glm::vec3& angle, glm::vec3& forward,
	                   glm::vec3& right, glm::vec3& lookat,
	                   glm::vec3& up);
	std::unique_ptr<Program> default_program;
	std::unique_ptr<Program> text_program;
	std::unique_ptr<Program> sky_program;
	std::shared_ptr<Texture> diffuse, specular;
	std::map<uint64_t, ChunkMesh> chunk_meshes;
	struct frustrum {
		glm::vec3 ntl, ntr, nbl, nbr;
		glm::vec3 ftl, ftr, fbl, fbr;
		float near_dist;
		float height_near, width_near;
		float far_dist;
		float height_far, width_far;
	};
	void ComputeFrustrum(glm::vec3 position, glm::vec3 lookAt);

	DirectionalLight sun;
	std::unique_ptr<Sky> sky;
};

