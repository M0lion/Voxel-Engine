#include "Chunk.h"
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "Shader.h"
#include "Functions.h"

const float Chunk::BLOCK_SIZE = 0.1f;

Chunk::Chunk(int x, int y, int z, Block *** blocks_ptr)
{
	this->x = x;
	this->y = y;
	this->z = z;

	blockCount = 0;

	if (blocks_ptr == 0)
	{
		blocks = new Block**[CHUNK_SIZE];
		for (int i = 0; i < CHUNK_SIZE; i++)
		{
			blocks[i] = new Block*[CHUNK_SIZE];

			for (int j = 0; j < CHUNK_SIZE; j++)
			{
				blocks[i][j] = new Block[CHUNK_SIZE];
				for (int k = 0; k < CHUNK_SIZE; k++)
				{
					if (j >(func(i + (x * CHUNK_SIZE) - 50, k + (z * CHUNK_SIZE) - 50) * 5) + 5)
						blocks[i][j][k].setActive(false);
					else
						blockCount++;


					float spacing = 0;
					if (j > 6)
						blocks[i][j][k].setBlockType(BlockType::Stone);
					else if (j > 2)
						blocks[i][j][k].setBlockType(BlockType::Grass);
					else
						blocks[i][j][k].setBlockType(BlockType::Water);
				}
			}
		}
	}
	else
		blocks = blocks_ptr;

	CreateMesh();
}


Chunk::~Chunk()
{
	for (int i = 0; i < CHUNK_SIZE; ++i)
	{
		for (int j = 0; j < CHUNK_SIZE; ++j)
		{
			delete[] blocks[i][j];
		}

		delete[] blocks[i];
	}
	delete[] blocks;
}

void Chunk::Update()
{

}

void Chunk::Draw()
{
	glm::mat4 model = glm::translate(glm::mat4(), glm::vec3(x * BLOCK_SIZE * CHUNK_SIZE, y * BLOCK_SIZE * CHUNK_SIZE, z * BLOCK_SIZE * CHUNK_SIZE));
	glUniformMatrix4fv(Shader::getCurrentShader()->getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));
	mesh->Draw();
}

void Chunk::CreateMesh()
{
	if (mesh != 0)
		delete(mesh);

	mesh = new Mesh();

	for (int i = 0; i < CHUNK_SIZE; i++)
	{
		for (int j = 0; j < CHUNK_SIZE; j++)
		{
			for (int k = 0; k < CHUNK_SIZE; k++)
			{
				float spacing = 0.5;
				if (blocks[i][j][k].isActive())
					blocks[i][j][k].CreateMesh(mesh, BLOCK_SIZE, i, j, k, blocks, CHUNK_SIZE);
			}
		}
	}
	mesh->Build();
}

Block ***Chunk::getBlocks()
{
	return blocks;
}

int Chunk::getBlockCount()
{
	return blockCount;
}