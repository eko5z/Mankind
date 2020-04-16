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
#include "GUI.hpp"

#include "Mesh.hpp"
#include "QuadMesh.hpp"
#include "DirectionalLight.hpp"
#include "HighlightMesh.hpp"
#include "GraphXManager.hpp"

class Renderer
{
public:
	Renderer(Game& g, GraphXManager& graphics_manager);
	~Renderer();

	void OpenWindow();
	void Render();
	void AddChunk(int x, int y, int z, Chunk& c);
	void SetGUI(std::shared_ptr<GUI> gui);
private:
	std::shared_ptr<GUI> gui;
	Game& game;
	GraphXManager& graphics_manager;
	int n_frames;
	int fps;
	int ms_accu, last_time;
	float h_fov, v_fov_rad, v_fov;
	void DrawSky();
	void DrawTerrain();
	void DrawGUI();
	void DrawHighlight();
	void DrawObjects();
	void LoadChunks();
	std::shared_ptr<Font> main_font;
	std::unique_ptr<TileManager> tile_manager;
	std::unique_ptr<HighlightMesh> highlight_mesh;
	int view_height, view_width;
	SDL_Window* window;
	SDL_GLContext context;
	std::unique_ptr<Program> default_program;
	std::unique_ptr<Program> gui_program;
	std::unique_ptr<Program> sky_program;
	std::unique_ptr<Program> highlight_program;
	std::map<uint64_t, ChunkMesh> chunk_meshes;

	DirectionalLight sun;
	std::unique_ptr<QuadMesh> sky;

	glm::mat4 view, projection;
};

