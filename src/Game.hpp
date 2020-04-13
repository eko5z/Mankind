#pragma once

#include "Terrain.hpp"
#include "Camera.hpp"
#include "ECS.hpp"
#include "TransformComponent.hpp"
#include "PhysicsComponent.hpp"
#include "PhysicsSystem.hpp"
#include "GraphicsComponent.hpp"
#include "GraphicsSystem.hpp"
#include "GraphXManager.hpp"
#include "InputComponent.hpp"
#include "InputSystem.hpp"

class Game
{
public:
	Game(GraphXManager& graphics_manager);
	~Game();
	bool KeepGoing()
	{
		return keep_going;
	}
	void Stop()
	{
		keep_going = false;
	}
	Terrain& GetTerrain()
	{
		return terrain;
	}
	Camera& GetCamera()
	{
		return camera;
	}
	void Update(float dt);
	glm::vec3 GetPlayerPosition()
	{
		return player->get<TransformComponent>()->position;
	}
	glm::vec3 GetPlayerRotation()
	{
		return player->get<TransformComponent>()->rotation;
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
		player->get<TransformComponent>()->position = v;
	}
	void SetPlayerRotation(glm::vec3 v)
	{
		player->get<TransformComponent>()->rotation = v;
	}
	void SetPlayerVelocity(glm::vec3 v)
	{
		player->get<PhysicsComponent>()->vel = v;
	}
	ECS::ComponentHandle<InputComponent> GetPlayerInputComponent()
	{
		return player->get<InputComponent>();
	}

	void Start(int seed);
	void OnPunch(glm::vec3 position, glm::vec3 lookat);
	void OnUse(glm::vec3 position, glm::vec3 lookat);
	void CalculatePointing(glm::vec3 position, glm::vec3 lookAt, float maxDistance, bool& is_pointing, glm::vec3& pointed, glm::vec3& normal);

	/* TODO: should go into a special factory */
	void CreateTree(glm::vec3 position);
private:
	/* TODO: this too should be moved to a factory */
	GraphXManager& graphics_manager;
	Terrain terrain;
	Camera camera;
	bool keep_going;
	ECS::Entity* player;
	ECS::Entity* tree;
	ECS::World* ecs_world;
	void PlaceCube(glm::vec3 position, Cube type);
	void DestroyCube(glm::vec3 position);

	void CreatePlayer();
};

