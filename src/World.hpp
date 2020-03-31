#pragma once

#include "Chunk.hpp"
#include <map>
#include <tuple>
#include <memory>

class Map
{
public:
	Cube& GetCube(int x, int y, int z);
	void SetCube(int x, int y, int z);
private:
	std::map<std::tuple<int, int, int>, std::unique_ptr<Chunk>> chunks;
}

