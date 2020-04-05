#include "TileManager.hpp"

TileManager::TileManager(std::string path, int n_tiles) :
	path(path),
	n_tiles(n_tiles),
	tile_size(1.f/n_tiles)
{
	diffuse = std::make_shared<Texture>(path + "_diffuse.png");
	specular = std::make_shared<Texture>(path + "_specular.png");
}

glm::vec2 TileManager::GetTileBottomRight(int typeID)
{
	return glm::vec2{0.f, (typeID-1) * tile_size};
}

glm::vec2 TileManager::GetTileBottomLeft(int typeID)
{
	return GetTileBottomRight(typeID) + glm::vec2{1.0f, 0.f};
}

glm::vec2 TileManager::GetTileTopRight(int typeID)
{
	return GetTileBottomRight(typeID) + glm::vec2{0.f, tile_size};
}

glm::vec2 TileManager::GetTileTopLeft(int typeID)
{
	return GetTileBottomRight(typeID) + glm::vec2{1.0f, tile_size};
}

