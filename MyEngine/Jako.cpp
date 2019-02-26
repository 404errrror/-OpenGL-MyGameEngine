#include "Jako.h"
#include "Player.h"
#include "Image.h"
#include "Animation.h"
#include "BoxCollider.h"


Jako::Jako()
{
	m_pImage = nullptr;
	SetName("Jako");
}


Jako::~Jako()
{
}


void Jako::Initialize()
{
	m_pImage = transform.AddComponent<Image>();
	m_pImage->SetSprite("JakoIdleImg_0");
	SetName("Jako");
	//m_pAnimation = &transform.AddComponent<Animation>();
	Enemy::Initialize();						// 꼭 이미지 컴포넌트 추가하고 초기화해야함.

	transform.SetScale(glm::vec3(0.1f));

	m_pAnimation->AddClip("Idle");
	m_pAnimation->SetFrame("Idle", "JakoIdleImg_0");
	m_pAnimation->SetFrame("Idle", "JakoIdleImg_1");
	m_pAnimation->SetClip("Idle");
	m_pAnimation->SetFrameDelay(0.2f);
	m_pAnimation->Play();

	m_pCollider->SetWidth(transform.GetScale().x);
	m_pCollider->SetHeight(transform.GetScale().y);

	m_score = 50;
}


void Jako::Start()
{
	Enemy::Start();

}


void Jako::Update()
{
	Enemy::Update();
	//std::cout << m_pPattern->GetRotateData().z << std::endl;
}


void Jako::Release()
{
	Enemy::Release();
}


void Jako::Die()
{
	Enemy::Die();
	if (m_isPlayBgm == false)
	{
		m_isPlayBgm = true;
		SoundManager::Play("ZakoHitted");
	}
}


void Jako::Attack()
{
	m_speed = 0.8f;
	if (m_pEndPattern->GetEndPosition().x >= 0)
	{
		m_pPattern->AddPattern(glm::vec3(0, 0, 270), 0.25f);
		m_pPattern->AddPattern(glm::vec3(0, 0, -180), 1.0f);
		m_pPattern->AddPattern(glm::vec3(0, 0, 360), 3.0f);
		m_pPattern->AddPattern(glm::vec3(0, 0, 90), 1.0f);
		m_pPattern->AddPattern(glm::vec3(0, 0, -45), 1.0f);
	}
	else
	{
		m_pPattern->AddPattern(glm::vec3(0, 0, -270), 0.25f);
		m_pPattern->AddPattern(glm::vec3(0, 0, 180), 1.0f);
		m_pPattern->AddPattern(glm::vec3(0, 0, -360), 3.0f);
		m_pPattern->AddPattern(glm::vec3(0, 0, -90), 1.0f);
		m_pPattern->AddPattern(glm::vec3(0, 0, 45), 1.0f);
	}
}


void Jako::AttackLoop()
{
	if (transform.GetPosition().x >= 0.8f)
	{
		m_pPattern->AddPattern(glm::vec3(0, 0, 100), 1.0f);
		m_pPattern->AddPattern(glm::vec3(0, 0, -80), 1.0f);
	}

	else if (transform.GetPosition().x <= -0.8f)
	{
		m_pPattern->AddPattern(glm::vec3(0, 0, -100), 1.0f);
		m_pPattern->AddPattern(glm::vec3(0, 0, 80), 1.0f);
	}

	else
	{
		if (m_pEndPattern->GetEndPosition().x >= 0)
		{
			m_pPattern->AddPattern(glm::vec3(0, 0, 90), 1.0f);
			m_pPattern->AddPattern(glm::vec3(0, 0, -90), 1.0f);
		}
		else
		{
			m_pPattern->AddPattern(glm::vec3(0, 0, -90), 1.0f);
			m_pPattern->AddPattern(glm::vec3(0, 0, 90), 1.0f);
		}
	}
}