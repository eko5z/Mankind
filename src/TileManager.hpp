#pragma once

#include <glm/glm.hpp>

#include <iostream>
#include <memory>

#include "Texture.hpp"

class TileManager
{
private:
	int n_tiles;
	float tile_size; // 0..1
	std::string path;
	std::shared_ptr<Texture> diffuse;
	std::shared_ptr<Texture> specular;
public:
	TileManager(std::string path, int n_tiles);
	glm::vec2 GetTileBottomRight(int typeID);
	glm::vec2 GetTileBottomLeft(int typeID);
	glm::vec2 GetTileTopRight(int typeID);
	glm::vec2 GetTileTopLeft(int typeID);

	std::shared_ptr<Texture> GetDiffuse()
	{
		return std::move(diffuse);
	}
	std::shared_ptr<Texture> GetSpecular()
	{
		return std::move(specular);
	}
};

