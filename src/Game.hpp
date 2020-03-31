#pragma once

#include "World.hpp"

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
private:
	World world;
	bool keep_going;
};

