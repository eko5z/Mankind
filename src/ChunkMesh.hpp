#pragma once

#include "GraphX.hpp"
#include "Chunk.hpp"
#include "Program.hpp"
#include "Mesh.hpp"

class ChunkMesh
{
private:
  Chunk& chunk;
  std::unique_ptr<Mesh> mesh;
  void Update();
public:
	ChunkMesh(Chunk& chunk);

  void Render();
};

