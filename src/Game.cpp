#include "Game.hpp"

Game::Game() :
	keep_going(true)
{
	camera.x = 0.;
	camera.y = 0.;
	camera.z = 0.;
	camera.yaw = 0.;
	camera.pitch = 0.;
	camera.roll = 0.;
}

