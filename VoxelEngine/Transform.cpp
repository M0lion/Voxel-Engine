#include "Transform.h"

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <math.h>
#include "Shader.h"

Transform::Transform()
{
}

void Transform::LoadToActiveShader(GLuint modelHandle)
{
	glm::mat4 model = glm::mat4();
	model = glm::rotate(model, xRot, glm::vec3(1, 0, 0));
	model = glm::rotate(model, yRot, glm::vec3(0, 1, 0));
	model = glm::rotate(model, zRot, glm::vec3(0, 0, 1));

	model = glm::translate(model, glm::vec3(xPos, yPos, zPos));

	model = glm::scale(model, glm::vec3(xScale, yScale, zScale));

	modelHandle = Shader::getCurrentShader()->getUniformLocation("model");
	glUniformMatrix4fv(modelHandle, 1, GL_FALSE, glm::value_ptr(model));
}

Transform::~Transform()
{
}

void Transform::Move(float x, float y, float z, bool relative)
{
	glm::mat4 transform = glm::rotate(glm::mat4(), xRot, glm::vec3(1, 0, 0));
	transform = glm::rotate(transform, yRot, glm::vec3(0, 1, 0));
	transform = glm::rotate(transform, zRot, glm::vec3(0, 0, 1));

	transform = glm::translate(transform, glm::vec3(x, y, z));
	glm::vec4 pos = glm::vec4(x, y, z, 1);
	pos = transform * pos;
	xPos += pos.x;
	yPos += pos.y;
	zPos += pos.z;
}

void Transform::Rotate(float x, float y, float z)
{
	xRot += x;
	yRot += y;
	zRot += z;
}