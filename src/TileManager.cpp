#include "TileManager.hpp"

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

