#include "Mesh.h"
#include "Shader.h"


Mesh::Mesh()
{
	vertices = 0;
	indices = 0;
	triangleCount = 0;

	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);

	currentNormal.x = 0;
	currentNormal.y = 0;
	currentNormal.z = 0;

	currentColor.r = 0;
	currentColor.g = 0;
	currentColor.b = 0;
	currentColor.a = 0;

	vertices = new std::vector<Vertex>();
	indices = new std::vector<Index>();
}


Mesh::~Mesh()
{
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);

	if (vertices != 0)
		delete(vertices);

	if (indices != 0)
		delete(vertices);
}

void Mesh::Build()
{
	GLfloat *vertexData = new GLfloat[vertexCount * vertexSize];

	int i = 0;
	for (std::vector<Vertex>::iterator it = vertices->begin(); it != vertices->end(); it++)
	{
		vertexData[i * vertexSize] = it->pos.x;
		vertexData[(i * vertexSize) + 1] = it->pos.y;
		vertexData[(i * vertexSize) + 2] = it->pos.z;
		vertexData[(i * vertexSize) + 3] = it->normal.x;
		vertexData[(i * vertexSize) + 4] = it->normal.y;
		vertexData[(i * vertexSize) + 5] = it->normal.z;
		vertexData[(i * vertexSize) + 6] = it->color.r;
		vertexData[(i * vertexSize) + 7] = it->color.g;
		vertexData[(i * vertexSize) + 8] = it->color.b;
		vertexData[(i * vertexSize) + 9] = it->color.a;
		i++;
	}

	GLuint *indexData = new GLuint[indexCount];
	i = 0;
	for (std::vector<Index>::iterator it = indices->begin(); it != indices->end(); it++)
	{
		indexData[i] = it->index;
		i++;
	}

	//VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertexCount * vertexSize, vertexData, GL_STATIC_DRAW);

	//EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indexCount, indexData, GL_STATIC_DRAW);

	glBindVertexArray(VAO);
	glEnableVertexAttribArray(SHADER_POS_HANDLE);
	glEnableVertexAttribArray(SHADER_NORMAL_HANDLE);
	glEnableVertexAttribArray(SHADER_COLOR_HANDLE);

	glVertexAttribPointer(SHADER_POS_HANDLE, 3, GL_FLOAT, GL_FALSE, vertexSize * sizeof(GLfloat), 0);
	glVertexAttribPointer(SHADER_NORMAL_HANDLE, 3, GL_FLOAT, GL_FALSE, vertexSize * sizeof(GLfloat), (void*)(sizeof(GLfloat) * 3));
	glVertexAttribPointer(SHADER_COLOR_HANDLE, 4, GL_FLOAT, GL_FALSE, vertexSize * sizeof(GLfloat), (void*)(sizeof(GLfloat) * 6));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	delete(vertexData);
	delete(indexData);
	vertices = 0;
	indices = 0;
}

int Mesh::addVertex(float posX, float posY, float posZ, float normalX, float normalY, float normalZ, float r, float g, float b, float a)
{
	if (vertices == 0)
	{
		vertices = new std::vector<Vertex>();
	}

	Vector pos;
	pos.x = posX;
	pos.y = posY;
	pos.z = posZ;

	Vector normal;
	normal.x = normalX;
	normal.y = normalY;
	normal.z = normalZ;

	Color color;
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;

	Vertex vertex;

	vertex.pos = pos;
	vertex.normal = normal;
	vertex.color = color;

	vertices->push_back(vertex);

	vertexCount++;
	return vertexCount - 1;
}

int Mesh::addVertex(float posX, float posY, float posZ)
{
	return addVertex(
		posX, posY, posZ, 
		currentNormal.x, currentNormal.y, currentNormal.z,
		currentColor.r, currentColor.g, currentColor.b, currentColor.a);
}

void Mesh::addIndex(GLuint i)
{
	if (indices == 0)
	{
		indices = new std::vector<Index>();
	}

	Index index;
	index.index = i;

	indices->push_back(index);

	indexCount++;
}

void Mesh::addTriangle(GLuint v1, GLuint v2, GLuint v3)
{
	addIndex(v1);
	addIndex(v2);
	addIndex(v3);
	triangleCount++;
}

void Mesh::Draw()
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::addNormal(float x, float y, float z)
{
	currentNormal.x = x;
	currentNormal.y = y;
	currentNormal.z = z;
}

void  Mesh::addColor(float r, float g, float b, float a)
{
	currentColor.r = r;
	currentColor.g = g;
	currentColor.b = b;
	currentColor.a = a;
}

//---------------------------------------------------------------

void Vertex::Delete()
{
	if (this->next != 0)
	{
		Vertex *current = this->next;
		while (current->next != 0)
		{
			Vertex *tmp = current;
			current = current->next;
			delete(tmp);
		}
		delete(current);
	}
	delete(this);
}

void Index::Delete()
{
	if (this->next != 0)
	{
		Index *current = this->next;
		while (current->next != 0)
		{
			Index *tmp = current;
			current = current->next;
			delete(tmp);
		}
		delete(current);
	}
	delete(this);
}