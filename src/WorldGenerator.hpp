#pragma once

#include <vector>
#include <cstdlib>

#include "Chunk.hpp"

class WorldGenerator
{
public:
	WorldGenerator(int seed);
	void GenerateChunk(Chunk& c);
private:
	int seed;
	int HeightAt(int x, int z);
	std::vector<int> p;
	double fade(double t);
	double lerp(double t, double a, double b);
	double grad(int hash, double x, double y, double z);
	double noise(double x, double y, double z);
};

