#include "Particle.h"

Particle::Particle()
{
	SetName("Particle");
	m_pImage = nullptr;
	m_fadeTime = 0.0f;
	m_time = 0.0f;
	m_fadeBaseAlpha = 1.0f;
}


Particle::~Particle()
{
}


void Particle::Initialize()
{
	GameObject::Initialize();
	m_pImage = transform.AddComponent<Image>();
	m_pImage->SetSprite("Point");
}


void Particle::Start()
{
	GameObject::Start();
	m_fadeTime = 0.0f;
	m_time = 0.0f;
}


void Particle::Update()
{
	GameObject::Update();
	m_time += Time::GetDeltaTime();
	if (m_fadeTime > 0.0f)
	{
		m_pImage->SetColorAlpha(m_fadeBaseAlpha - m_fadeBaseAlpha * (m_time / m_fadeTime));
		if (m_time / m_fadeTime >= 1.0f)
			m_remove = true;
	}
}


void Particle::Release()
{
	GameObject::Release();
}


Image* Particle::GetImage()
{
	return m_pImage;
}


void Particle::SetFade(float time)
{
	m_fadeTime = time;
	m_fadeBaseAlpha = m_pImage->GetColor().a;
}