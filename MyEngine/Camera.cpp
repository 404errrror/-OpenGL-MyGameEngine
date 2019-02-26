#include "Camera.h"

glm::mat4	Camera::projection;
glm::mat4	Camera::view;
glm::mat4	Camera::ortho = glm::ortho
							(
								- (float)g_width/ (float)g_height, 
								(float)g_width / (float)g_height,
								-1.0f, 1.0f, 
								0.0f, 100.0f
							);
glm::mat4	Camera::orthoView;
bool		Camera::m_isPerspective;

Camera::Camera()
{
	m_isPerspective = false;
}


Camera::~Camera()
{
}


void Camera::SetProjection(float viewAngle, float screenRatio,
	float minRender, float maxRender)
{
	projection = glm::perspective(
		viewAngle,
		screenRatio,
		minRender,
		maxRender
	);
}


void Camera::SetView(glm::vec3 position, glm::vec3 viewPosition, glm::vec3 up)
{
	view = glm::lookAt(
		position,
		viewPosition,
		up);
}


void Camera::SetOrthoView(glm::vec3 position, glm::vec3 viewPosition, glm::vec3 up)
{
	orthoView = glm::lookAt(
		position,
		viewPosition,
		up);
}



glm::mat4 Camera::GetVP()
{
	if (m_isPerspective)
		return projection * view;
	else
		return ortho * orthoView;
}


glm::mat4 Camera::GetOrthoVP()
{
	return ortho * orthoView;
}


void Camera::PerspectiveButton(bool isPerspective)
{
	m_isPerspective = isPerspective;
}