#include "MouseManager.h"
#include "GameObject.h"
#include "CameraC.h"

glm::vec2 MouseManager::screenPosition;
glm::vec2 MouseManager::position;
float MouseManager::speed;

MouseManager::State MouseManager::leftState;
MouseManager::State MouseManager::rightState;

MouseManager::MouseManager()
{
	screenPosition = glm::vec2(0.0f);
	position = glm::vec2(0.0f);
	speed = 1.0f;
	leftState = None;
	rightState = None;
}


MouseManager::~MouseManager()
{
}


void MouseManager::Initialize()
{
	glfwSetCursorPos(g_window, g_width / 2, g_height / 2);
	screenPosition = glm::vec2(g_width * 0.5f, g_height * 0.5f);
	speed = 1.0f;
	leftState = None;
	rightState = None;
}


void MouseManager::Update()
{
	static glm::vec2 center = glm::vec2(g_width * 0.5f, g_height * 0.5f);
	double mousePosX, mousePosY;
	glfwGetCursorPos(g_window, &mousePosX, &mousePosY);

	screenPosition += (glm::vec2(mousePosX, mousePosY) - center) * speed * Time::GetDeltaTime() * 60.0f;

	// 화면 밖으로 마우스가 나가지 않도록.
		if (screenPosition.x > g_width)
			screenPosition.x = g_width;
		else if (screenPosition.x < 0)
			screenPosition.x = 0;
		if (screenPosition.y > g_height)
			screenPosition.y = g_height;
		else if (screenPosition.y < 0)
			screenPosition.y = 0;

	position = ScreenToWorld(screenPosition);
	if (CameraC::main != nullptr)
	{
		glm::vec3 cameraPosition = CameraC::main->gameObject.transform.GetPosition();
		position -= glm::vec2(cameraPosition.x, cameraPosition.y);
	}

	UpdateState();


	glfwSetCursorPos(g_window, g_width / 2, g_height / 2);
}


glm::vec2 MouseManager::GetPosition()
{
	return position;
}


float MouseManager::GetPositionX()
{
	return position.x;
}


float MouseManager::GetPositionY()
{
	return position.y;
}


MouseManager::State MouseManager::GetLeftState()
{
	return leftState;
}


MouseManager::State MouseManager::GetRightState()
{
	return rightState;
}


void MouseManager::UpdateState()
{
	// left update
	int state = glfwGetMouseButton(g_window, GLFW_MOUSE_BUTTON_LEFT);

	if (state == GLFW_PRESS)
	{
		if (leftState == None || leftState == Up)
			leftState = Press;
		else
			leftState = Pressing;
	}
	else // state == GLFW_RELEASE
	{
		if (leftState == Pressing || leftState == Press)
			leftState = Up;
		else
			leftState = None;
	}

	// right update
	state = glfwGetMouseButton(g_window, GLFW_MOUSE_BUTTON_RIGHT);

	if (state == GLFW_PRESS)
	{
		if (rightState == None || rightState == Up)
			rightState = Press;
		else
			rightState = Pressing;
	}
	else // state == GLFW_RELEASE
	{
		if (rightState == Pressing || rightState == Press)
			rightState = Up;
		else
			rightState = None;
	}

}