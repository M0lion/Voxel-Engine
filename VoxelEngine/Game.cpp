#include "Game.h"
#include "Shader.h"
#include "Mesh.h"

#include <stdio.h>

static int blocks = 0;

Game::Game()
{
	if (!glfwInit())
	{
		throw "Could not initialize glfw";
	}

	window = glfwCreateWindow(windowWidth, windowHeight, "ProcTest", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		throw "Could not create window";
	}

	glfwMakeContextCurrent(window);
	printf("OpenGL version: %s/n", glGetString(GL_VERSION));

	glfwSetKeyCallback(window, keyCallback);

	//glewExperimental = GL_TRUE;
	glewInit();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
	glBlendEquationSeparate(GL_FUNC_ADD, GL_MAX);

	glClearColor(0, 0, 0, 1);

	camera = new Camera(window);
	gamePads = new GamepadManager();

	Shader *shader = new Shader("blockShader.vsh", "blockShader.fsh");
	shader->Activate();
	camera->loadToShader(); 

	chunks.data = new Chunk();
	current = &chunks;
	blocks += current->data->getBlockCount();
	c = 1;
	while (c <= 10)
	{
		for (int i = 0; i < c; i++)
		{
			current->next = new LinkedList<Chunk>();
			current = current->next;
			current->data = new Chunk(i, 0, c);
			blocks += current->data->getBlockCount();

			current->next = new LinkedList<Chunk>();
			current = current->next;
			current->data = new Chunk(c, 0, i);
			blocks += current->data->getBlockCount();
		}
		current->next = new LinkedList<Chunk>();
		current = current->next;
		current->data = new Chunk(c, 0, c);

		c++;
	}
	printf("Blocks: %d/n", blocks);

	run();
}


Game::~Game()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

void Game::run()
{
	while (!glfwWindowShouldClose(window))
	{
		Update();		Draw();

		GLenum error;
		while ((error = glGetError()) != GL_NO_ERROR)
			fprintf(stderr, "OpenGL error: %s/n", gluErrorString(error));

		glfwPollEvents();
	}
}

void Game::Update()
{
	gamePads->Update();
	camera->Update((bool*)keys, gamePads);

	if (gamePads->getButton(2))
	{
		for (int i = 0; i < c; i++)
		{
			current->next = new LinkedList<Chunk>();
			current = current->next;
			current->data = new Chunk(i, 0, c);
			blocks += current->data->getBlockCount();

			current->next = new LinkedList<Chunk>();
			current = current->next;
			current->data = new Chunk(c, 0, i);
			blocks += current->data->getBlockCount();
		}
		current->next = new LinkedList<Chunk>();
		current = current->next;
		current->data = new Chunk(c, 0, c);


		c++;
		printf("Blocks: %d/n", blocks);
	}
}

void Game::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	camera->loadToShader();
	//mesh->Draw();
	LinkedList<Chunk> *current = &chunks;
	while (current->next != 0)
	{
		current->data->Draw();
		current = current->next;
	}
	current->data->Draw();

	glfwSwapBuffers(window);
}

bool Game::keys[] = { false };
void Game::keyCallback(GLFWwindow* sender, int key, int scancode, int action, int mods)
{
	keys[key] = action != GLFW_RELEASE;
}