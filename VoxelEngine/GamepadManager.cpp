#include "GamepadManager.h"
#include <GLFW\glfw3.h>
#include <math.h>

GamepadManager::GamepadManager()
{
	reset();
}

GamepadManager::~GamepadManager()
{
}

void GamepadManager::reset()
{
	axes = 0;
	axesCount = -1;

	buttons = 0;
	buttonCount = -1;
}

void GamepadManager::Update()
{
	reset();
	for (int i = 0; i <= GLFW_JOYSTICK_LAST; i++)
	{
		if (glfwJoystickPresent(i) == GL_TRUE)
		{
			const float *tmpAxes = glfwGetJoystickAxes(i, &axesCount);
			buttons = glfwGetJoystickButtons(i, &buttonCount);

			delete(axes);
			axes = new float[axesCount];

			for (int j = 0; j < axesCount; j++)
			{
				if (abs(tmpAxes[j]) > 0.20)
					axes[j] = tmpAxes[j];// (int)(10 * tmpAxes[j]) / 10.;
				else
					axes[j] = 0;
			}

			break;
		}
	}
}

float GamepadManager::getAxis(int axis)
{
	if (axis < axesCount)
		return axes[axis];
	else
		return 0;
}

bool GamepadManager::getButton(int button)
{
	if (button < buttonCount)
		return buttons[button] == GLFW_PRESS;
	else
		return false;
}
