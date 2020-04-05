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
#include "HighlightMesh.hpp"

class Renderer
{
public:
	Renderer(Game& g);
	~Renderer();

	void OpenWindow();
	void Render();
	void AddChunk(int x, int y, int z, Chunk& c);
private:
	Game& game;
	int n_frames;
	int fps;
	int ms_accu, last_time;
	GLint uniform_mvp;
	float h_fov, v_fov_rad, v_fov;
	void DrawSky();
	void DrawTerrain();
	void DrawGUI();
	void DrawHighlight();
	void LoadChunks();
	std::shared_ptr<Font> main_font;
	std::unique_ptr<GUILabel> position_label, version_label, fps_label;
	std::unique_ptr<TileManager> tile_manager;
	std::unique_ptr<HighlightMesh> highlight_mesh;
	int view_height, view_width;
	SDL_Window* window;
	SDL_GLContext context;
	void UpdateVectors(glm::vec3& angle, glm::vec3& forward,
	                   glm::vec3& right, glm::vec3& lookat,
	                   glm::vec3& up);
	std::unique_ptr<Program> default_program;
	std::unique_ptr<Program> text_program;
	std::unique_ptr<Program> sky_program;
	std::unique_ptr<Program> highlight_program;
	std::map<uint64_t, ChunkMesh> chunk_meshes;

	DirectionalLight sun;
	std::unique_ptr<Sky> sky;
};

