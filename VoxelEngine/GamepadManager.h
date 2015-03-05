#pragma once
class GamepadManager
{
public:
	GamepadManager();
	~GamepadManager();

	void Update();

	float getAxis(int axis);
	bool getButton(int button);
private:
	float *axes;
	int axesCount;

	const unsigned char *buttons;
	int buttonCount;

	void reset();
};

