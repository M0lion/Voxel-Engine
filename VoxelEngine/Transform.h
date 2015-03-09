#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Transform
{
public:
	Transform();
	~Transform();

	//translates the transform, if relative is false move in world-space, else in model-space
	void Move(float x, float y, float z, bool relative);
	void Rotate(float x, float y, float z);

	void LoadToActiveShader(GLuint modelHandle);
private:
	float xPos = 0, yPos = 0, zPos = 0;
	float xRot = 0, yRot = 0, zRot = 0;
	float xScale = 0, yScale = 0, zScale = 0;
};