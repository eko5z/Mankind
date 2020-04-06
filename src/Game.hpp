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
	glm::vec3 GetPlayerBox()
	{
		return player->get<PhysicsComponent>()->box_whd;
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
	void OnPunch(glm::vec3 position, glm::vec3 lookat);
	void OnUse(glm::vec3 position, glm::vec3 lookat);
	void CalculatePointing(glm::vec3 position, glm::vec3 lookAt, float maxDistance, bool& is_pointing, glm::vec3& pointed, glm::vec3& normal);
private:
	World world;
	Camera camera;
	bool keep_going;
	ECS::Entity* player;
	ECS::World* ecs_world;
	void PlaceCube(glm::vec3 position, Cube type);
	void DestroyCube(glm::vec3 position);

	void CreatePlayer();
};

