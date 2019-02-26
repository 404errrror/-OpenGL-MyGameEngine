#pragma once
#include "Global.h"
class InputManager
{
public:
	InputManager();
	~InputManager();

	static bool IsKeyDown(int keyCode);
	static bool IsKeyDownOnce(int keyCode);
	static void KeyUpdate();

	static bool key[400];
};