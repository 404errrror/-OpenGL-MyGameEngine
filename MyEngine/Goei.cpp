#include "Goei.h"
#include "Player.h"
#include "Image.h"
#include "Animation.h"
#include "BoxCollider.h"


Goei::Goei()
{
	m_pImage = nullptr;
	SetName("Goei");
}


Goei::~Goei()
{
}


void Goei::Initialize()
{
	m_pImage = transform.AddComponent<Image>();
	m_pImage->SetSprite("GoeiIdleImg_0");
	SetName("Goei");
	//m_pAnimation = &transform.AddComponent<Animation>();
	Enemy::Initialize();						// 꼭 이미지 컴포넌트 추가하고 초기화해야함.

	transform.SetScale(glm::vec3(0.1f));

	m_pAnimation->AddClip("Idle");
	m_pAnimation->SetFrame("Idle", "GoeiIdleImg_0");
	m_pAnimation->SetFrame("Idle", "GoeiIdleImg_1");
	m_pAnimation->SetClip("Idle");
	m_pAnimation->SetFrameDelay(0.2f);
	m_pAnimation->Play();

	m_pCollider->SetWidth(transform.GetScale().x);
	m_pCollider->SetHeight(transform.GetScale().y);

	m_score = 80;
}


void Goei::Start()
{
	Enemy::Start();

}


void Goei::Update()
{
	Enemy::Update();

}


void Goei::Release()
{
	Enemy::Release();
}


void Goei::Die()
{
	Enemy::Die();
	if (m_isPlayBgm == false)
	{
		m_isPlayBgm = true;
		SoundManager::Play("GoeiHitted");
	}
}


void Goei::Attack()
{
	m_speed = 0.8f;
	if (m_pEndPattern->GetEndPosition().x >= 0)
	{
		m_pPattern->AddPattern(glm::vec3(0, 0, 180), 0.25f);
		m_pPattern->AddPattern(glm::vec3(0, 0, 0), 0.25f);
		m_pPattern->AddPattern(glm::vec3(0, 0, 405), 1.0f);
		m_pPattern->AddPattern(glm::vec3(0, 0, -45), 1.0f);
		m_pPattern->AddPattern(glm::vec3(0, 0, 45), 1.0f);

	}
	else
	{
		m_pPattern->AddPattern(glm::vec3(0, 0, -180), 0.25f);
		m_pPattern->AddPattern(glm::vec3(0, 0, 0), 0.25f);
		m_pPattern->AddPattern(glm::vec3(0, 0, -405), 1.0f);
		m_pPattern->AddPattern(glm::vec3(0, 0, 45), 1.0f);
		m_pPattern->AddPattern(glm::vec3(0, 0, -45), 1.0f);
	}
}


void Goei::AttackLoop()
{
	if (m_pEndPattern->GetEndPosition().x >= 0)
	{
		m_pPattern->AddPattern(glm::vec3(0, 0, -90), 1.0f);
		m_pPattern->AddPattern(glm::vec3(0, 0, 90), 1.0f);
	}
	else
	{
		m_pPattern->AddPattern(glm::vec3(0, 0, 90), 1.0f);
		m_pPattern->AddPattern(glm::vec3(0, 0, -90), 1.0f);
	}
}