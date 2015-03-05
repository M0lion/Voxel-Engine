#include "Block.h"


Block::Block()
{
	Block::Block(BlockType::Default, true);
}

Block::Block(BlockType blockType, bool active)
{
	this->blockType = blockType;
	this->active = active;
}

bool Block::isActive()
{
	return active;
}

void Block::setActive(bool active)
{
	this->active = active;
}

BlockType Block::getBlockType()
{
	return blockType;
}

void Block::setBlockType(BlockType blockType)
{
	this->blockType = blockType;
}

Block::~Block()
{
}

void Block::CreateMesh(Mesh *mesh, float blockSize, int i, int j, int k, Block ***blocks, int chunkSize)
{
	float spacing = 0;
	blockSize += spacing;

	float x = i * blockSize;
	float y = j * blockSize;
	float z = k * blockSize;

	blockSize -= spacing;

	Color color;
	switch (blockType)
	{
		case BlockType::Dirt:
		{
			mesh->addColor(0.3, 0.5, 0.59, 1);
		}break;
		case BlockType::Grass:
		{
			mesh->addColor(0, 1, 0, 1);
		}break;
		case BlockType::Water:
		{
			mesh->addColor(0, 0, 1, 1);
		}break;
		case BlockType::Stone:
		{
			mesh->addColor(0.5, 0.5, 0.5, 1);
		}break;
		default:
		{
			mesh->addColor(1, 1, 1, 1);
		}break;
	}


	bool drawFront = true;
	if (k > 0)
		if (blocks[i][j][k - 1].isActive())
			drawFront = false;
	bool drawBack = true;
	if (k + 1 < chunkSize)
		if (blocks[i][j][k + 1].isActive())
			drawBack = false;

	bool drawRight = true;
	if (i > 0)
		if (blocks[i - 1][j][k].isActive())
			drawRight = false;
	bool drawLeft = true;
	if (i + 1 < chunkSize)
		if (blocks[i + 1][j][k].isActive())
			drawLeft = false;

	bool drawUp = true;
	if (j +1 < chunkSize)
		if (blocks[i][j + 1][k].isActive())
			drawUp = false;
	bool drawDown = true;
	if (j > 0)
		if (blocks[i][j - 1][k].isActive())
			drawDown = false;


	//front
	if (drawFront)
	{
		mesh->addNormal(0, 0, -1);
		int f0 = mesh->addVertex(x + 0, y + 0, z + 0);
		int f1 = mesh->addVertex(x + 0, y + -blockSize, z + 0);
		int f2 = mesh->addVertex(x + blockSize, y + -blockSize, z + 0);
		int f3 = mesh->addVertex(x + blockSize, y + 0, z + 0);

		mesh->addTriangle(f0, f1, f2);
		mesh->addTriangle(f2, f3, f0);
	}

	//back
	if (drawBack)
	{
		mesh->addNormal(0, 0, 1);
		int b0 = mesh->addVertex(x + 0, y + 0, z + blockSize);
		int b3 = mesh->addVertex(x + blockSize, y + 0, z + blockSize);
		int b2 = mesh->addVertex(x + blockSize, y + -blockSize, z + blockSize);
		int b1 = mesh->addVertex(x + 0, y + -blockSize, z + blockSize);

		mesh->addTriangle(b0, b1, b2);
		mesh->addTriangle(b2, b3, b0);
	}

	//right
	if (drawRight)
	{
		mesh->addNormal(-1, 0, 0);
		int r0 = mesh->addVertex(x + 0, y + 0, z + 0);
		int r1 = mesh->addVertex(x + 0, y + 0, z + blockSize);
		int r2 = mesh->addVertex(x + 0, y + -blockSize, z + blockSize);
		int r3 = mesh->addVertex(x + 0, y + -blockSize, z + 0);

		mesh->addTriangle(r0, r1, r2);
		mesh->addTriangle(r2, r3, r0);
	}

	//left
	if (drawLeft)
	{
		mesh->addNormal(1, 0, 0);
		int l0 = mesh->addVertex(x + blockSize, y + 0, z + 0);
		int l3 = mesh->addVertex(x + blockSize, y + -blockSize, z + 0);
		int l2 = mesh->addVertex(x + blockSize, y + -blockSize, z + blockSize);
		int l1 = mesh->addVertex(x + blockSize, y + 0, z + blockSize);

		mesh->addTriangle(l0, l1, l2);
		mesh->addTriangle(l2, l3, l0);
	}

	//up
	if (drawUp)
	{
		mesh->addNormal(0, 1, 0);
		int u0 = mesh->addVertex(x + 0, y + 0, z + 0);
		int u1 = mesh->addVertex(x + blockSize, y + 0, z + 0);
		int u2 = mesh->addVertex(x + blockSize, y + 0, z + blockSize);
		int u3 = mesh->addVertex(x + 0, y + 0, z + blockSize);

		mesh->addTriangle(u0, u1, u2);
		mesh->addTriangle(u2, u3, u0);
	}

	//down
	if (drawDown)
	{
		mesh->addNormal(0, -1, 0);
		int d0 = mesh->addVertex(x + 0, y + -blockSize, z + 0);
		int d3 = mesh->addVertex(x + 0, y + -blockSize, z + blockSize);
		int d2 = mesh->addVertex(x + blockSize, y + -blockSize, z + blockSize);
		int d1 = mesh->addVertex(x + blockSize, y + -blockSize, z + 0);

		mesh->addTriangle(d0, d1, d2);
		mesh->addTriangle(d2, d3, d0);
	}
}