#include "MainInputManager.hpp"
#include "Log.hpp"
#include <glm/glm.hpp>

MainInputManager::MainInputManager(Game& g) :
	InputManager::InputManager(g),
	going_forward(false),
	going_backward(false),
	going_leftward(false),
	going_rightward(false),
	jumping(false)
{
}

void MainInputManager::ChangePlayerVelocity()
{
	auto player_vel = game.GetPlayerVelocity();
	auto player_rot = game.GetPlayerRotation();
	glm::vec3 forward, right;
	forward.x = sinf(player_rot.x);
	forward.y = 0;
	forward.z = cosf(player_rot.x);

	right.x = -cosf(player_rot.x);
	right.y = 0;
	right.z = sinf(player_rot.x);

	forward = glm::normalize(forward);
	right = glm::normalize(right);
	float velocity_scale = 5;
	player_vel.x = 0;
	player_vel.z = 0;
	if (going_forward) {
		player_vel.x += forward.x * velocity_scale;
		player_vel.z += forward.z * velocity_scale;
	} else if (going_backward) {
		player_vel.x -= forward.x * velocity_scale;
		player_vel.z -= forward.z * velocity_scale;
	}

	if (going_rightward) {
		player_vel.x += right.x * velocity_scale;
		player_vel.z += right.z * velocity_scale;
	} else if (going_leftward) {
		player_vel.x -= right.x * velocity_scale;
		player_vel.z -= right.z * velocity_scale;
	}

	if (jumping) {
		player_vel.y = 5;
		jumping = false;
	}

	game.SetPlayerVelocity(player_vel);
}

void MainInputManager::OnKeyDown(char key, bool repeat)
{

	switch (key) {
	case 'w':
		going_forward = true;
		break;
	case 's':
		going_backward = true;
		break;
	case 'a':
		going_leftward = true;
		break;
	case 'd':
		going_rightward = true;
		break;
	case ' ':
		jumping = true;
		break;
	}
	ChangePlayerVelocity();
}

void MainInputManager::OnKeyUp(char key)
{
	auto player_vel = game.GetPlayerVelocity();
	auto player_rot = game.GetPlayerRotation();
	glm::vec3 forward, right;
	forward.x = sinf(player_rot.x);
	forward.y = 0;
	forward.z = cosf(player_rot.y);

	right.x = -cosf(player_rot.x);
	right.y = 0;
	right.z = sinf(player_rot.x);

	forward = glm::normalize(forward);
	right = glm::normalize(right);

	switch (key) {
	case 'w':
		going_forward = false;
		break;
	case 's':
		going_backward = false;
		break;
	case 'a':
		going_leftward = false;
		break;
	case 'd':
		going_rightward = false;
		break;
	case 'r':
		game.SetPlayerPosition(glm::vec3(0, 100, 0));
		break;
	case ' ':
		jumping = false;
		break;
	}

	ChangePlayerVelocity();
}

void MainInputManager::OnMouseButtonDown(MouseButton button)
{
}

void MainInputManager::OnMouseButtonUp(MouseButton button)
{
	Camera& c = game.GetCamera();
	glm::vec3 position(c.x, c.y, c.z);
	glm::vec3 lookat( sinf(c.yaw) * cosf(c.pitch),
	                  sinf(c.pitch),
	                  cosf(c.yaw) * cosf(c.pitch));
	CalculatePointing(game.GetWorld(), position, lookat, 5.0);

	/* TODO: use OnPunch(x,y,z,normal) and OnUse(x,y,z,normal) instead */
	if (button == MouseButton::LEFT) {
		if (is_pointing) {
			game.GetWorld().SetCube(pointed_cube.x, pointed_cube.y, pointed_cube.z, Cube{0});
		}
	} else if (button == MouseButton::RIGHT) {
		if (is_pointing) {
			glm::vec3 to_build(pointed_cube + pointed_normal);
			game.GetWorld().SetCube(to_build.x, to_build.y, to_build.z, Cube{1});
		}
	}
}

void MainInputManager::OnMouseMotion(int x, int y, int dx, int dy)
{
	auto rot = game.GetPlayerRotation();
	rot += glm::vec3(-dx / 500., -dy / 500., 0.);
	game.SetPlayerRotation(rot);
	ChangePlayerVelocity();
}

void MainInputManager::OnQuit()
{
	game.Stop();
}

void MainInputManager::CalculatePointing(World& world, glm::vec3 position, glm::vec3 lookAt, float maxDistance)
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
					pointed_normal = glm::vec3(-1, 0, 0);
				} else {
					pointed_normal = glm::vec3(1, 0, 0);
				}
			} else {
				// Z face
				current_voxel[2] += stepZ;
				tMaxZ += tDeltaZ;

				if (position.z < current_voxel.z) {
					pointed_normal = glm::vec3(0, 0, -1);
				} else {
					pointed_normal = glm::vec3(0, 0, 1);
				}
			}
		} else {
			if (tMaxY < tMaxZ) {
				// Y face
				current_voxel[1] += stepY;
				tMaxY += tDeltaY;

				if (position.y < current_voxel.y) {
					pointed_normal = glm::vec3(0, -1, 0);
				} else {
					pointed_normal = glm::vec3(0, 1, 0);
				}
			} else {
				// Z face
				current_voxel[2] += stepZ;
				tMaxZ += tDeltaZ;

				if (position.z < current_voxel.z) {
					pointed_normal = glm::vec3(0, 0, -1);
				} else {
					pointed_normal = glm::vec3(0, 0, 1);
				}
			}
		}
		if (world.GetCube(current_voxel.x, current_voxel.y, current_voxel.z).typeID != 0) {
			is_pointing = true;
			pointed_cube = current_voxel;
			return;
		}
	}
}

