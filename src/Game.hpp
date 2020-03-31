#pragma once

#include "World.hpp"
#include "Camera.hpp"

class Game
{
public:
	Game();
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
private:
	World world;
	Camera camera;
	bool keep_going;
};

