#pragma once

#include "World.hpp"
#include "Camera.hpp"
#include "ECS.hpp"
#include "TransformComponent.hpp"
#include "PhysicsComponent.hpp"
#include "PhysicsSystem.hpp"

class Game
{
public:
	Game();
	~Game();
	bool KeepGoing()
	{
		return keep_going;
	}
	void Stop()
	{
		keep_going = false;
	}
	World& GetWorld()
	{
		return world;
	}
	Camera& GetCamera()
	{
		return camera;
	}
	void Update(float dt);
	glm::vec3 GetPlayerPosition()
	{
		return player->get<TransformComponent>()->pos;
	}
	glm::vec3 GetPlayerRotation()
	{
		return player->get<TransformComponent>()->rot;
	}
	glm::vec3 GetPlayerVelocity()
	{
		return player->get<PhysicsComponent>()->vel;
	}
	void SetPlayerPosition(glm::vec3 v)
	{
		player->get<TransformComponent>()->pos = v;
	}
	void SetPlayerRotation(glm::vec3 v)
	{
		player->get<TransformComponent>()->rot = v;
	}
	void SetPlayerVelocity(glm::vec3 v)
	{
		player->get<PhysicsComponent>()->vel = v;
	}
	void Start(int seed);
private:
	World world;
	Camera camera;
	bool keep_going;
	ECS::Entity* player;
	ECS::World* ecs_world;

	void CreatePlayer();
};

