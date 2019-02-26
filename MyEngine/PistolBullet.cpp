#include "PistolBullet.h"



PistolBullet::PistolBullet()
{
	m_pLine = nullptr;
}


PistolBullet::~PistolBullet()
{
}


void PistolBullet::Initialize()
{
	GameObject::Initialize();
	m_pLine = transform.AddComponent<Line>();
	m_color = glm::vec4(1.0f);
	m_damage = 1;
}


void PistolBullet::Update()
{
	if (m_color.a <= 0)
		m_remove = true;
	else
	{
		m_color -= glm::vec4(0.0f, 0.0f, 0.0f, Time::GetDeltaTime() * 2);
		m_pLine->SetColor(m_color);
	}
}


void PistolBullet::Shoot(glm::vec2 startPoint, glm::vec2 endPoint)
{
	m_pLine->SetPoint(startPoint, endPoint);
}