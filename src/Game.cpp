#include "Game.hpp"

#include "Log.hpp"

void Game::Start(int seed)
{
	world.Generate(seed);
	SetPlayerPosition(glm::vec3{0, world.GetSpawnHeight(0, 0), 0});
	std::cerr << "Player spawns at y=" << GetPlayerPosition().y << std::endl;
}

void Game::CreatePlayer()
{
	player = ecs_world->create();
	player->assign<TransformComponent>();
	player->assign<PhysicsComponent>();
}

Game::Game() :
	keep_going(true),
	ecs_world(ECS::World::createWorld())
{
	ecs_world->registerSystem(new PhysicsSystem(world));
	CreatePlayer();
}

Game::~Game()
{
	ecs_world->destroyWorld();
}

void Game::Update(float dt)
{
	ecs_world->tick(dt);
	world.Update(dt);
	auto campos = GetPlayerPosition();
	auto camrot = GetPlayerRotation();
	camera.x = campos.x;
	camera.y = campos.y + 1.6; /* player is a Neanderthal 1,60 m Chad */
	camera.z = campos.z;
	camera.yaw = camrot.x;
	camera.pitch = camrot.y;
	camera.roll = camrot.z;
}

