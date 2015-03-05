#pragma once

#include "Block.h"
#include "Mesh.h"

class Chunk
{
public:
	Chunk(int x = 0, int y = 0, int z = 0, Block ***blocks = 0);
	~Chunk();

	void Update();
	void Draw();

	Block ***getBlocks();

	int getBlockCount();

	static const float BLOCK_SIZE;
	static const int CHUNK_SIZE = 10;
private:
	Block ***blocks;

	int blockCount;

	Mesh *mesh;

	int x;
	int y;
	int z;

	void CreateMesh();
};