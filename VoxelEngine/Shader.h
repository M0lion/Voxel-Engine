#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>

#define SHADER_POS_HANDLE 0
#define SHADER_NORMAL_HANDLE 1
#define SHADER_COLOR_HANDLE 2

class Shader
{
public:
	Shader(GLchar *vertexShader, GLchar *fragmentShader);
	~Shader();

	void Activate();
	static Shader *getCurrentShader();

	GLint getUniformLocation(const GLchar *name);
	GLint getAttribLocation(const GLchar *name);
private:
	static Shader *currentShader;

	GLuint shaderProgram;
	GLuint modelHandle;
	GLuint viewHandle;
	GLuint projectionHandle;
	GLuint lightHandle;
};

