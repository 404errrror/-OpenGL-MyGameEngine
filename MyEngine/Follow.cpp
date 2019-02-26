#include "Follow.h"
#include "Transform.h"
#include "GameObject.h"

std::list<Follow*> Follow::list;

Follow::Follow(GameObject& gameObject) : Component(gameObject)
{
	list.push_back(this);
	m_pTarget = nullptr;
	m_speed = 2.0f;
}


Follow::~Follow()
{
}


void Follow::Initialize()
{
	Component::Initialize();
}


void Follow::Update()
{
	if (m_pTarget != nullptr)
	{
		gameObject.transform.SetPosition(gameObject.transform.GetPosition() * -1.0f);
		glm::vec3 dir = m_pTarget->GetPosition() - gameObject.transform.GetPosition();
		dir.z = 0;
		float speed = Time::GetDeltaTime() * m_speed;
		//if (speed > 1.0f)
		//	speed = 1.0f;
		gameObject.transform.Translate(dir *speed, true);
		gameObject.transform.SetPosition(gameObject.transform.GetPosition() * -1.0f);
	}

}


void Follow::Release()
{
	Component::Release();
}


void Follow::SetTarget(Transform* target)
{
	m_pTarget = target;
}


void Follow::SetFollowSpeed(float speed)
{
	m_speed = speed;
}