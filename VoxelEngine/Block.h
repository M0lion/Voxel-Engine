#pragma once

#include "Mesh.h"

enum BlockType
{
	Default = 0,

	Grass,
	Dirt,
	Water,
	Stone,
	Wood,
	Sand,

	NumTypes,
};

class Block
{
public:
	Block();
	Block(BlockType	blockType, bool active);
	~Block();

	bool isActive();
	void setActive(bool active);

	BlockType getBlockType();
	void setBlockType(BlockType blockType);

	void CreateMesh(Mesh *mesh, float blockSize, int x, int y, int z, Block ***blocks, int chunkSize);
private:
	bool active;
	BlockType blockType;
};

