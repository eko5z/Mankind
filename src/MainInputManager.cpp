#include "MainInputManager.hpp"
#include "Log.hpp"
#include <glm/glm.hpp>

void MainInputManager::OnKeyDown(char key)
{
	Camera& c = game.GetCamera();
	glm::vec3 forward, right;
	forward.x = sinf(c.yaw);
	forward.y = 0;
	forward.z = cosf(c.yaw);

	right.x = -cosf(c.yaw);
	right.y = 0;
	right.z = sinf(c.yaw);

	switch (key) {
	case 'w':
		game.GetCamera().x += forward.x * 2;
		game.GetCamera().y += forward.y * 2;
		game.GetCamera().z += forward.z * 2;
		break;
	case 's':
		game.GetCamera().x -= forward.x * 2;
		game.GetCamera().y -= forward.y * 2;
		game.GetCamera().z -= forward.z * 2;
		break;
	case 'a':
		game.GetCamera().x -= right.x * 2;
		game.GetCamera().y -= right.y * 2;
		game.GetCamera().z -= right.z * 2;
		break;
	case 'd':
		game.GetCamera().x += right.x * 2;
		game.GetCamera().y += right.y * 2;
		game.GetCamera().z += right.z * 2;
		break;
	case 'q':
		game.GetCamera().y += 1;
		break;
	case 'e':
		game.GetCamera().y -= 1;
		break;
	}
}

void MainInputManager::OnKeyUp(char key)
{
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
	if (is_pointing) {
		game.GetWorld().SetCube(pointed_cube.x, pointed_cube.y, pointed_cube.z, Cube{0});
	}
}

void MainInputManager::OnMouseMotion(int x, int y, int dx, int dy)
{
	Camera& c = game.GetCamera();
	c.yaw -= dx / 500.;
	c.pitch -= dy / 500.;
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

