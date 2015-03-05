#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "Camera.h"
#include "Mesh.h"
#include "Chunk.h"

#define KEYS 348

class Game
{
public:
	Game();
	~Game();

	void Update();
	void Draw();

	void run();

private:

	int windowWidth = 640;
	int windowHeight = 460;

	GLFWwindow *window;

	Camera *camera;
	LinkedList<Chunk> chunks;
	LinkedList<Chunk> *current;
	int c;

	GamepadManager *gamePads;

	static bool keys[KEYS];//actual type is bool[KEYS]; -- KEYS defined in Windows3D.cpp

	static void keyCallback(GLFWwindow* sender, int key, int scancode, int action, int mods);

};

