#include "Renderer.hpp"

#include <stdexcept>
#include <config.h>

#include "Log.hpp"

Renderer::Renderer() :
	window(nullptr),
	chunk_program(nullptr)
{
	LOG("Initializing renderer");
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		throw std::runtime_error(SDL_GetError());
	}
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
}

Renderer::~Renderer()
{
	LOG("Destroying renderer");
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Renderer::OpenWindow()
{
	LOG("Opening window");
	window = SDL_CreateWindow(PACKAGE_STRING,
	                          SDL_WINDOWPOS_CENTERED,
	                          SDL_WINDOWPOS_CENTERED,
	                          500, 500,
	                          SDL_WINDOW_SHOWN |
	                          SDL_WINDOW_OPENGL);
	if (window == nullptr) {
		throw std::runtime_error(SDL_GetError());
	}
	LOG("Creating GL context");
	context = SDL_GL_CreateContext(window);
	if (context == nullptr) {
		throw std::runtime_error(SDL_GetError());
	}
	LOG("Initializing GLEW");
	if (glewInit() != GLEW_OK) {
		throw std::runtime_error("Error initializing GLEW");
	}
	LOG("All initialized. Loading resources");

	chunk_program = std::make_unique<Program>("res/shaders/cube.vert", "res/shaders/cube.frag");
	LOG("Window correctly opened");

	texture = std::make_unique<Texture>("res/tex/stone.png");
	attribute_coord = chunk_program->GetAttrib("coord");
	glClearColor(0.6, 0.8, 1.0, 0.0);
	glEnableVertexAttribArray(attribute_coord);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	chunk_program->Use();
	glUniform1i(uniform_texture, 0);
}

void Renderer::Render(World& world, Camera& camera)
{
	AddChunk(0, 0, 0, world.GetChunk(0, 0, 0));

	glm::mat4 view = glm::LookAt(position, position + lookat, up);

	glClear(GL_COLOR_BUFFER_BIT);
	for (auto kc : chunk_meshes) {
		kc.second.Render(*chunk_program);
	}
	SDL_GL_SwapWindow(window);
}

void Renderer::AddChunk(int x, int y, int z, Chunk& c)
{
	chunk_meshes.insert(std::make_pair(CHUNK_ID(x, y, z), ChunkMesh(c)));
}

