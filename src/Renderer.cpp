#include "Renderer.hpp"

#include <config.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Log.hpp"

Renderer::Renderer() :
	window(nullptr),
	default_program(nullptr),
	sun(glm::vec3{0.3, 1.0, 0.8},
	    glm::vec3{0.2, 0.2, 0.2},
	    glm::vec3{0.5, 0.5, 0.5},
	    glm::vec3{0.5, 0.5, 0.5})
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
	int ccx(camera.x / 16),
	    ccy(camera.y / 16),
	    ccz(camera.z / 16);

	// Add a chunk.
	for (int i(ccx-5); i < ccx+5; ++i) {
		for (int j(ccy-5); j < ccz+5; ++j) {
			for (int k(ccz-5); k < ccz+5; ++k) {
				if (chunk_meshes.find(CHUNK_ID(i, j, k)) == chunk_meshes.end()) {
					this->AddChunk(world, i, j, k, world.GetChunk(i, j, k));
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
	// Lighting things.
	this->sun.AddToProgram(*(this->default_program), 0);
	default_program->SetFloat("shininess", 2.0f);

	for(auto& kc : this->chunk_meshes) {
		int x(kc.second.GetX() * CHUNK_SIZE),
		    y(kc.second.GetY() * CHUNK_SIZE),
		    z(kc.second.GetZ() * CHUNK_SIZE);
		glm::mat4 translate = glm::translate(glm::mat4(), glm::vec3(x, y, z));
		glm::mat4 mvp = projection * view * translate;
		glUniformMatrix4fv(uniform_mvp, 1, GL_FALSE, glm::value_ptr(mvp));

		kc.second.Render();
	}
	CalculatePointing(world, position, lookat, 5.0);
	if (is_pointing) {
		world.SetCube(pointed_cube.x, pointed_cube.y, pointed_cube.z, Cube{0});
	}

	SDL_GL_SwapWindow(window);
}

void Renderer::ComputeFrustrum(glm::vec3 position, glm::vec3 lookAt)
{
	static glm::vec3 up(0., 1., 0.), right(1., 0., 0.);
	lookAt = glm::normalize(lookAt);
}

void Renderer::CalculatePointing(World& world, glm::vec3 position, glm::vec3 lookAt, float maxDistance)
{
	float _bin_size = 1;
	is_pointing = false;
	glm::vec3 ray_start(position);
	// This id of the first/current voxel hit by the ray.
	// Using floor (round down) is actually very important,
	// the implicit int-casting will round up for negative numbers.
	glm::vec3 current_voxel(std::floor(ray_start[0]/_bin_size),
	                        std::floor(ray_start[1]/_bin_size),
	                        std::floor(ray_start[2]/_bin_size));

	glm::vec3 ray_end(position + glm::normalize(lookAt) * maxDistance);
	// The id of the last voxel hit by  = current_voxelthe ray.
	// TODO: what happens if the end point is on a border?
	glm::vec3 last_voxel(std::floor(ray_end[0]/_bin_size),
	                     std::floor(ray_end[1]/_bin_size),
	                     std::floor(ray_end[2]/_bin_size));

	// Compute normalized ray direction.
	glm::vec3 ray = ray_end-ray_start;
	//ray.normalize();

	// In which direction the voxel ids are incremented.
	float stepX = (ray[0] >= 0) ? 1:-1; // correct
	float stepY = (ray[1] >= 0) ? 1:-1; // correct
	float stepZ = (ray[2] >= 0) ? 1:-1; // correct

	// Distance along the ray to the next voxel border from the current position (tMaxX, tMaxY, tMaxZ).
	float next_voxel_boundary_x = (current_voxel[0]+stepX)*_bin_size; // correct
	float next_voxel_boundary_y = (current_voxel[1]+stepY)*_bin_size; // correct
	float next_voxel_boundary_z = (current_voxel[2]+stepZ)*_bin_size; // correct

	// tMaxX, tMaxY, tMaxZ -- distance until next intersection with voxel-border
	// the value of t at which the ray crosses the first vertical voxel boundary
	float tMaxX = (ray[0]!=0) ? (next_voxel_boundary_x - ray_start[0])/ray[0] : DBL_MAX; //
	float tMaxY = (ray[1]!=0) ? (next_voxel_boundary_y - ray_start[1])/ray[1] : DBL_MAX; //
	float tMaxZ = (ray[2]!=0) ? (next_voxel_boundary_z - ray_start[2])/ray[2] : DBL_MAX; //

	// tDeltaX, tDeltaY, tDeltaZ --
	// how far along the ray we must move for the horizontal component to equal the width of a voxel
	// the direction in which we traverse the grid
	// can only be FLT_MAX if we never go in that direction
	float tDeltaX = (ray[0]!=0) ? _bin_size/ray[0]*stepX : DBL_MAX;
	float tDeltaY = (ray[1]!=0) ? _bin_size/ray[1]*stepY : DBL_MAX;
	float tDeltaZ = (ray[2]!=0) ? _bin_size/ray[2]*stepZ : DBL_MAX;

	glm::vec3 diff(0,0,0);
	bool neg_ray=false;
	if (current_voxel[0]!=last_voxel[0] && ray[0]<0) {
		diff[0]--;
		neg_ray=true;
	}
	if (current_voxel[1]!=last_voxel[1] && ray[1]<0) {
		diff[1]--;
		neg_ray=true;
	}
	if (current_voxel[2]!=last_voxel[2] && ray[2]<0) {
		diff[2]--;
		neg_ray=true;
	}
	if (neg_ray) {
		current_voxel+=diff;
	}

	while(last_voxel != current_voxel) {
		if (tMaxX < tMaxY) {
			if (tMaxX < tMaxZ) {
				current_voxel[0] += stepX;
				tMaxX += tDeltaX;
			} else {
				current_voxel[2] += stepZ;
				tMaxZ += tDeltaZ;
			}
		} else {
			if (tMaxY < tMaxZ) {
				current_voxel[1] += stepY;
				tMaxY += tDeltaY;
			} else {
				current_voxel[2] += stepZ;
				tMaxZ += tDeltaZ;
			}
		}
		if (world.GetCube(current_voxel.x, current_voxel.y, current_voxel.z).typeID != 0) {
			is_pointing = true;
			pointed_cube = current_voxel;
			return;
		}
	}
}

void Renderer::AddChunk(World& world, int x, int y, int z, Chunk& c)
{
	std::cerr << "Adding chunk " << CHUNK_ID(x, y, z) << "("<<x<<", "<<y<<", "<<z<<")" << std::endl;
	this->chunk_meshes.insert(std::make_pair(CHUNK_ID(x, y, z), ChunkMesh(world, c, x, y, z, diffuse, specular)));
}
