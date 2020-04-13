#include "Game.hpp"

#include "Log.hpp"

void Game::Start(int seed)
{
	this->keep_going = true;
	this->ecs_world = ECS::World::createWorld();
	this->ecs_world->registerSystem(new InputSystem());
	this->ecs_world->registerSystem(new PhysicsSystem(this->terrain));
	this->ecs_world->registerSystem(new GraphicsSystem(*this, graphics_manager));
	this->CreatePlayer();

	terrain.SetTerrainGenerator(std::make_unique<TerrainGenerator>(*this, seed));
	SetPlayerPosition(glm::vec3{0, terrain.GetSpawnHeight(0, 0), 0});
	SetPlayerRotation(glm::vec3{-3.14159/2.f, 0, 0}); /* look on the Z axis */
	CreateTree(glm::vec3(0, terrain.GetSpawnHeight(0, 0) + 4, 0));
	std::cerr << "Player spawns at y=" << GetPlayerPosition().y << std::endl;
}

void Game::CreatePlayer()
{
	player = ecs_world->create();
	player->assign<TransformComponent>();
	player->assign<PhysicsComponent>();
	player->assign<InputComponent>();
	player->get<PhysicsComponent>()->box_whd = glm::vec3(1.5, 3.2, 1.5);
}

Game::Game(GraphXManager& graphics_manager):
	graphics_manager(graphics_manager),
	camera(800, 600)
{

}

Game::~Game()
{
	ecs_world->destroyWorld();
}

void Game::Update(float dt)
{
	ecs_world->tick(dt);
	terrain.Update(dt);
	/* this places campos in the exact middle of the box */
	auto campos = GetPlayerPosition() + GetPlayerBox() / 2.f;
	float eyes_height(1.6 / CUBE_SIZE / 2.); /* player is a Neanderthal 1,60 m Chad */
	camera.position = campos + glm::vec3(0, eyes_height, 0);
	camera.rotation = GetPlayerRotation();
}

void Game::OnPunch(glm::vec3 position, glm::vec3 lookat)
{
	bool is_pointing;
	glm::vec3 pointed, normal;
	CalculatePointing(position, lookat, 10., is_pointing, pointed, normal);
	if (is_pointing) {
		DestroyCube(pointed);
	} else {
	}
}

void Game::OnUse(glm::vec3 position, glm::vec3 lookat)
{
	bool is_pointing;
	glm::vec3 pointed, normal;
	CalculatePointing(position, lookat, 10., is_pointing, pointed, normal);
	if (is_pointing) {
		/* TODO: place if holding a cube in the inventory */
		PlaceCube(pointed + normal, Cube{1});
	} else {
	}
}

void Game::PlaceCube(glm::vec3 position, Cube type)
{
	/* TODO: trigger 'OnPlaceCube' */
	terrain.SetCube(position.x, position.y, position.z, type);
}

void Game::DestroyCube(glm::vec3 position)
{
	/* TODO: trigger 'OnDestroyCube' */
	terrain.SetCube(position.x, position.y, position.z, Cube{0});
}

void Game::CreateTree(glm::vec3 position)
{
	auto t = ecs_world->create();
	t->assign<TransformComponent>();
	auto tc = t->get<TransformComponent>();
	tc->position = position;
	tc->rotation = glm::vec3{0, 0, 0}; // TODO: sum math king figure out how rotation works in OpenGL
	graphics_manager.GetBillBoardScale("tree_diffuse", tc->scale);
	tc->position.y += tc->scale.y / 2;
	t->assign<GraphicsComponent>();
	auto gc = t->get<GraphicsComponent>();
	gc->meshID = graphics_manager.GetMeshID("tree");
	gc->textureID[0] = graphics_manager.GetTextureID("tree_diffuse");
	gc->textureID[1] = -1;
	gc->textureID[2] = -1;
	gc->textureID[3] = -1;
	gc->programID = graphics_manager.GetProgramID("billboard");
}

void Game::CalculatePointing(glm::vec3 position, glm::vec3 lookAt, float maxDistance, bool& is_pointing, glm::vec3& pointed, glm::vec3& normal)
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
				// X face
				current_voxel[0] += stepX;
				tMaxX += tDeltaX;

				if (position.x < current_voxel.x) {
					normal = glm::vec3(-1, 0, 0);
				} else {
					normal = glm::vec3(1, 0, 0);
				}
			} else {
				// Z face
				current_voxel[2] += stepZ;
				tMaxZ += tDeltaZ;

				if (position.z < current_voxel.z) {
					normal = glm::vec3(0, 0, -1);
				} else {
					normal = glm::vec3(0, 0, 1);
				}
			}
		} else {
			if (tMaxY < tMaxZ) {
				// Y face
				current_voxel[1] += stepY;
				tMaxY += tDeltaY;

				if (position.y < current_voxel.y) {
					normal = glm::vec3(0, -1, 0);
				} else {
					normal = glm::vec3(0, 1, 0);
				}
			} else {
				// Z face
				current_voxel[2] += stepZ;
				tMaxZ += tDeltaZ;

				if (position.z < current_voxel.z) {
					normal = glm::vec3(0, 0, -1);
				} else {
					normal = glm::vec3(0, 0, 1);
				}
			}
		}
		if (terrain.GetCube(current_voxel.x, current_voxel.y, current_voxel.z).typeID != 0) {
			is_pointing = true;
			pointed = current_voxel;
			return;
		}
	}
}
