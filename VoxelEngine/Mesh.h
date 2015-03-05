#pragma once
#include "Types.h"
#include <GL/glew.h>
#include <vector>

struct Vertex
{
	Vector pos;
	Vector normal;
	Color color;
	Vertex *next;

	void Delete();
};
typedef Vertex* VertexList;

struct Index
{
	int index;
	Index *next;

	void Delete();
};
typedef Index* IndexList;

class Mesh
{
public:
	Mesh();
	~Mesh();

	void Build();
	int addVertex(float posX, float posY, float posZ, float normalX, float normalY, float normalZ, float r, float g, float b, float a);
	int addVertex(float posX, float posY, float posZ);
	void addTriangle(GLuint v1, GLuint v2, GLuint v3);

	void addNormal(float normalX, float normalY, float normalZ);
	void addColor(float r, float g, float b, float a);

	void Draw();
private:
	GLuint VBO;
	GLuint EBO;
	GLuint VAO;

	std::vector<Vertex> *vertices;
	int vertexCount;
	std::vector<Index> *indices;
	int indexCount;
	int triangleCount;

	void addIndex(GLuint i);

	const int vertexSize = 10;

	Vector currentNormal;
	Color currentColor;
};

