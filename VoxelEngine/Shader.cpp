#include "Shader.h"
#include "ShaderUtils.h"
#include <stdio.h>


Shader::Shader(GLchar *VertexShader, GLchar *FragmentShader)
{
	GLuint vertexShader = createShaderFromFile(VertexShader, GL_VERTEX_SHADER);
	GLuint fragmentShader = createShaderFromFile(FragmentShader, GL_FRAGMENT_SHADER);

	shaderProgram = glCreateProgram();

	if (shaderProgram == 0)
	{
		fprintf(stderr, "Could not create ShaderProgram/n");
		return;
	}

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glBindFragDataLocation(shaderProgram, 0, "fragData");
	glBindAttribLocation(shaderProgram, SHADER_POS_HANDLE, "position");
	glBindAttribLocation(shaderProgram, SHADER_NORMAL_HANDLE, "normal");
	glBindAttribLocation(shaderProgram, SHADER_COLOR_HANDLE, "color");


	glLinkProgram(shaderProgram);
	GLint linkStatus;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkStatus);
	if (linkStatus != GL_TRUE)
	{
		fprintf(stderr, "Program link failed!/n");

		GLint infoLength;
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLength);

		GLchar *info = new GLchar[infoLength + 1];
		glGetProgramInfoLog(shaderProgram, infoLength + 1, NULL, info);
		fprintf(stderr, "%s/n", info);
		delete info;
	}

	modelHandle = glGetUniformLocation(shaderProgram, "model");
	viewHandle = glGetUniformLocation(shaderProgram, "view");
	projectionHandle = glGetUniformLocation(shaderProgram, "projection");
}

GLint Shader::getUniformLocation(const GLchar *name)
{
	return glGetUniformLocation(shaderProgram, name);
}

GLint Shader::getAttribLocation(const GLchar *name)
{
	return glGetAttribLocation(shaderProgram, name);
}

void Shader::Activate()
{
	currentShader = this;
	glUseProgram(shaderProgram);
}

Shader::~Shader()
{
	glDeleteProgram(shaderProgram);
}

Shader* Shader::currentShader = 0;
Shader* Shader::getCurrentShader()
{
	return currentShader;
}