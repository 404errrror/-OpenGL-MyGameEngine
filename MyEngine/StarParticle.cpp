#include "StarParticle.h"
#include "Image.h"


StarParticle::StarParticle()
{
}


StarParticle::~StarParticle()
{
}


void StarParticle::Initialize()
{
	GameObject::Initialize();
	m_pImage = transform.AddComponent<Image>();
	m_pImage->SetSprite("Star");
	m_active = false;

	for (int i = 0; i < STAR_AMOUNT; ++i)
	{
		m_position[i] = glm::vec3(Random::Range(-1.5, 1.5), Random::Range(-1.5,1.5),0);
		m_remainTime[i] = m_glitterTime[i] = Random::Range(0.2f, 1.0f);
		m_alpha[i] = m_nowAlpha[i] = Random::Range(0.2f, 1.0f);
	}
}


void StarParticle::Start()
{
	GameObject::Start();
	transform.SetScale(glm::vec3(0.01f, 0.01f, 0.01f));
}


void StarParticle::Update()
{
	if (m_isStart == false)
		Start();
	GameObject::Update();

	for (int i = 0; i < STAR_AMOUNT; ++i)
	{
		m_position[i].y -= 0.5f * Time::GetDeltaTime();
		m_remainTime[i] -= Time::GetDeltaTime();

		if (m_remainTime[i] <= 0)
		{
			m_remainTime[i] = m_glitterTime[i];
			if (m_nowAlpha[i] != 0)
				m_nowAlpha[i] = 0;
			else
				m_nowAlpha[i] = m_alpha[i];
		}

		if (m_position[i].y < -1.5f)
			m_position[i].y *= -1;

		transform.SetPosition(m_position[i]);
		m_pImage->SetColor(glm::vec4(1, 1, 1, m_nowAlpha[i]));
		m_pImage->Update();
	}
}


void StarParticle::Release()
{
	GameObject::Release();
}