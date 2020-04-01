#include "Chunk.hpp"

#include <cstdlib>

void Chunk::Generate(int seed)
{
	srand(seed);
	for (int i(0); i < CHUNK_SIZE; ++i) {
		for (int j(0); j < CHUNK_SIZE; ++j) {
			for (int k(0); k < CHUNK_SIZE; ++k) {
				int n = rand() % 100;
				if (n) {
					SetCube(i, j, k, Cube{0});
				} else {
					SetCube(i, j, k, Cube{1});
				}
			}
		}
	}
}

