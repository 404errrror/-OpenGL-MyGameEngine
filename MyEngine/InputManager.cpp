#include "InputManager.h"

bool InputManager::key[400] = { false, };

InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}


bool InputManager::IsKeyDown(int keyCode)
{
	if (glfwGetKey(g_window, keyCode) == GLFW_PRESS)
	{
		key[GLFW_PRESS] = true;
		return true;
	}
	else 
		return false;
}


bool InputManager::IsKeyDownOnce(int keyCode)
{
	if (glfwGetKey(g_window, keyCode) == GLFW_PRESS && key[keyCode] == false)
	{
		key[keyCode] = true;
		return true;
	}
	else
		return false;
}


void InputManager::KeyUpdate()
{
	for (int i = 0; i < 400; ++i)
		if (key[i] == true)
			if (glfwGetKey(g_window, i) == GLFW_RELEASE)
				key[i] = false;
}