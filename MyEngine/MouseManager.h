#pragma once
#include "Global.h"
class GameObject;
class MouseManager
{
public:
	enum State
	{
		None, Press, Pressing, Up
	};
public:
	MouseManager();
	~MouseManager();

	static void Initialize();
	static void Update();

	static glm::vec2 GetPosition();
	static float GetPositionX();
	static float GetPositionY();

	static State GetLeftState();
	static State GetRightState();
private:
	static void UpdateState();
private:
	static glm::vec2 screenPosition;
	static glm::vec2 position;
	static float speed;
	static State leftState;
	static State rightState;
};

