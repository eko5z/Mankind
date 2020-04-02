#pragma once

#include <glm/glm.hpp>

#include <iostream>

class TileManager
{
private:
	int n_tiles;
	float tile_size; // 0..1
public:
	TileManager(int n_tiles) : n_tiles(n_tiles), tile_size(1.f/n_tiles) {}
	glm::vec2 GetTileBottomRight(int typeID);
	glm::vec2 GetTileBottomLeft(int typeID);
	glm::vec2 GetTileTopRight(int typeID);
	glm::vec2 GetTileTopLeft(int typeID);
};

