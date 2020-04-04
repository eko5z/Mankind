#include "Renderer.hpp"

#include <config.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Log.hpp"

Renderer::Renderer() :
	window(nullptr),
	default_program(nullptr),
	sun(glm::vec3{0.3, 1.0, 0.3},
	    glm::vec3{0.5, 0.5, 0.5},
	    glm::vec3{1.0, 1.0, 1.0})
{
	LOG("Initializing renderer");

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		throw std::runtime_error(SDL_GetError());
	}

	if (TTF_Init() == -1) {
		throw std::runtime_error(TTF_GetError());
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
}

Renderer::~Renderer()
{
	LOG("Destroying renderer");

	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
	TTF_Quit();
}

void Renderer::OpenWindow()
{
	LOG("Opening window");

	window = SDL_CreateWindow(PACKAGE_STRING,
	                          SDL_WINDOWPOS_CENTERED,
	                          SDL_WINDOWPOS_CENTERED,
	                          900, 700,
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

	main_font = std::make_shared<Font>("res/fonts/DejaVuSansMono.ttf", 24);
	position_label = std::make_unique<GUILabel>("position", main_font, "Position goes here");

	diffuse = std::make_shared<Texture>("res/tex/tiles_diffuse.png");
	specular = std::make_shared<Texture>("res/tex/tiles_specular.png");

	// Load the default program.
	this->default_program = std::make_unique<Program>("res/shaders/default.vert", "res/shaders/default.frag");

	LOG("Window correctly opened");

	glClearColor(0.6, 0.8, 1.0, 0.0);
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
	// find out camera chunk
	int ccx(camera.x / CHUNK_SIZE),
	    ccy(camera.y / CHUNK_SIZE),
	    ccz(camera.z / CHUNK_SIZE);

	// Add a chunk.
	for (int i(ccx-5); i < ccx+5; ++i) {
		for (int j(ccy-5); j < ccy+5; ++j) {
			for (int k(ccz-5); k < ccz+5; ++k) {
				int64_t chunkid = CHUNK_ID(i, j, k);
				if (chunk_meshes.find(CHUNK_ID(i, j, k)) == chunk_meshes.end()) {
					this->AddChunk(world, i, j, k, world.GetChunk(i, j, k));
				} else {
				}
			}
		}
	}

	GLint uniform_mvp = default_program->GetUniform("MVP");

	SDL_GetWindowSize(window, &view_width, &view_height);

	glm::vec3 position(camera.x, camera.y, camera.z);
	glm::vec3 angle(camera.yaw, camera.pitch, camera.roll);
	glm::vec3 forward, right, lookat, up;
	UpdateVectors(angle, forward, right, lookat, up);
	glm::mat4 view = glm::lookAt(position, position + lookat, up);
	glm::mat4 projection = glm::perspective(45.0f, 1.0f*view_width/view_height, 0.01f, 1000.0f);

	ComputeFrustrum(position, lookat);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POLYGON_OFFSET_FILL);

	this->default_program->Use();
	default_program->SetVec3("camera_position", position);
	this->sun.AddToProgram(*(this->default_program), 0);

	for(auto& kc : this->chunk_meshes) {
		int x(kc.second.GetX() * CHUNK_SIZE),
		    y(kc.second.GetY() * CHUNK_SIZE),
		    z(kc.second.GetZ() * CHUNK_SIZE);
		glm::mat4 translate = glm::translate(glm::mat4(), glm::vec3(x, y, z));
		glm::mat4 mvp = projection * view * translate;
		glUniformMatrix4fv(uniform_mvp, 1, GL_FALSE, glm::value_ptr(mvp));

		kc.second.Render();
	}

	glDisable(GL_DEPTH_TEST);

	auto ortho = glm::ortho(0.f, (float)view_width, (float)view_height, 0.f, 0.f, 1000.f);
	glUniformMatrix4fv(uniform_mvp, 1, GL_FALSE, glm::value_ptr(ortho));
	position_label->Draw();

	SDL_GL_SwapWindow(window);
}

void Renderer::ComputeFrustrum(glm::vec3 position, glm::vec3 lookAt)
{
	static glm::vec3 up(0., 1., 0.), right(1., 0., 0.);
	lookAt = glm::normalize(lookAt);
}

void Renderer::AddChunk(World& world, int x, int y, int z, Chunk& c)
{
	std::cerr << "Adding chunk " << x << "," << y << "," << z << std::endl;
	this->chunk_meshes.insert(std::make_pair(CHUNK_ID(x, y, z), ChunkMesh(world, c, x, y, z, diffuse, specular)));
}
