
#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include "GamepadManager.h"

class Camera
{
public:
	Camera(GLFWwindow *window);
	~Camera();

	void loadToShader();
	void Update(bool keys[], GamepadManager *gamePads);
private:
	void UpdateView();
	void UpdateProjection();

	void Move(float forward, float side, float up);

	GLFWwindow *window;

	GLuint lastShaderLoadedTo = 0;

	float xPos, yPos, zPos;
	float xRot, yRot, zRot;

	glm::mat4 projection;
	glm::mat4 view;
};

