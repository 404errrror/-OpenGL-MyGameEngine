#include "CameraTarget.h"
#include "M_Player.h"

CameraTarget* CameraTarget::instance;

CameraTarget::CameraTarget()
{
	if (instance == nullptr)
	{
		instance = this;
	}
	else
	{
		m_active = false;
		m_remove = true;
	}
}


CameraTarget::~CameraTarget()
{
}


void CameraTarget::Initialize()
{
	GameObject::Initialize();
}


void CameraTarget::Start()
{
	GameObject::Start();
}


void CameraTarget::Update()
{
	GameObject::Update();
	glm::vec2 playerPosition = glm::vec2(M_Player::instance->transform.GetPosition().x, M_Player::instance->transform.GetPosition().y);
	glm::vec2 mousePosition = MouseManager::GetPosition();
	transform.SetPosition(glm::vec3(playerPosition.x, playerPosition.y, 0.0f));
	transform.Translate(glm::vec3(mousePosition.x - playerPosition.x, mousePosition.y - playerPosition.y, 0.0f) * 0.1f, true);
}


void CameraTarget::Release()
{
	if (instance == this)
	{
		instance = nullptr;
	}
}