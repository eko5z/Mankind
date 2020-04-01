#include "Renderer.hpp"

#include <stdexcept>
#include <config.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

void Renderer::UpdateVectors(glm::vec3& angle, glm::vec3& forward,
                             glm::vec3& right, glm::vec3& lookat,
                             glm::vec3& up)
{
	forward.x = sinf(angle.x);
	forward.y = 0;
	forward.z = cosf(angle.x);
	right.x = -cosf(angle.x);
	right.y = 0;
	right.z = sinf(angle.x);
	lookat.x = sinf(angle.x) * cosf(angle.y);
	lookat.y = sinf(angle.y);
	lookat.z = cosf(angle.x) * cosf(angle.y);
	up = glm::cross(right, lookat);
}

void Renderer::Render(World& world, Camera& camera)
{
	AddChunk(0, 0, 0, world.GetChunk(0, 0, 0));
	GLint uniform_mvp = chunk_program->GetUniform("mvp");
	SDL_GetWindowSize(window, &view_width, &view_height);

	glm::vec3 position(camera.x, camera.y, camera.z);
	glm::vec3 angle(camera.yaw, camera.pitch, camera.roll);
	glm::vec3 forward, right, lookat, up;
	UpdateVectors(angle, forward, right, lookat, up);
	glm::mat4 view = glm::lookAt(position, position + lookat, up);
	glm::mat4 projection = glm::perspective(45.0f, 1.0f*view_width/view_height, 0.01f, 1000.0f);

	glm::mat4 mvp = projection * view;
	glUniformMatrix4fv(uniform_mvp, 1, GL_FALSE, glm::value_ptr(mvp));

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POLYGON_OFFSET_FILL);
	for (auto kc : chunk_meshes) {
		kc.second.Render(*chunk_program);
	}
	//DrawCrosshair();
	SDL_GL_SwapWindow(window);
}

void Renderer::DrawCrosshair()
{
	static float cross[4][4] = {
		{-0.05, 0, 0, 13},
		{+0.05, 0, 0, 13},
		{0, -0.05, 0, 13},
		{0, +0.05, 0, 13},
	};
	GLint uniform_mvp = chunk_program->GetUniform("mvp");
	glDisable(GL_DEPTH_TEST);
	glm::mat4 one(1);
	glUniformMatrix4fv(uniform_mvp, 1, GL_FALSE, glm::value_ptr(one));
	glBufferData(GL_ARRAY_BUFFER, sizeof(cross), cross, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(attribute_coord, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_LINES, 0, 4);
}

void Renderer::AddChunk(int x, int y, int z, Chunk& c)
{
	chunk_meshes.insert(std::make_pair(CHUNK_ID(x, y, z), ChunkMesh(c)));
}

