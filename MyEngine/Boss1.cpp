#include "Boss1.h"
#include "Player.h"
#include "Image.h"
#include "Animation.h"
#include "BoxCollider.h"
#include "Bullet.h"


Boss1::Boss1()
{
	m_pImage = nullptr;
	SetName("Boss1");
}


Boss1::~Boss1()
{
}


void Boss1::Initialize()
{
	m_pImage = transform.AddComponent<Image>();
	m_pImage->SetSprite("Boss1IdleImg_0");
	SetName("Boss1");
	//m_pAnimation = &transform.AddComponent<Animation>();
	Enemy::Initialize();						// 꼭 이미지 컴포넌트 추가하고 초기화해야함.

	transform.SetScale(glm::vec3(0.1f));

	m_pAnimation->AddClip("Idle");
	m_pAnimation->SetFrame("Idle", "Boss1IdleImg_0");
	m_pAnimation->SetFrame("Idle", "Boss1IdleImg_1");
	m_pAnimation->AddClip("Idle2");
	m_pAnimation->SetFrame("Idle2", "Boss2IdleImg_0");
	m_pAnimation->SetFrame("Idle2", "Boss2IdleImg_1");
	m_pAnimation->SetClip("Idle");

	m_pAnimation->SetFrameDelay(0.2f);
	m_pAnimation->Play();

	m_pCollider->SetWidth(transform.GetScale().x);
	m_pCollider->SetHeight(transform.GetScale().y);

	m_score = 50;
	m_hp = 2;
}


void Boss1::Start()
{
	Enemy::Start();
}


void Boss1::Update()
{
	Enemy::Update();

}


void Boss1::Release()
{
	Enemy::Release();
}


void Boss1::Die()
{
	Enemy::Die();
	if (m_isPlayBgm == false)
	{
		m_isPlayBgm = true;
		SoundManager::Play("Boss2Hitted");
	}
}


bool Boss1::HittedCheck()
{

	for (std::list<Bullet*>::iterator it = Bullet::myList.begin(); it != Bullet::myList.end(); ++it)
	{
		if (m_pCollider->CollisionCheck(glm::vec2((*it)->transform.GetPosition())))
		{
			std::cout << "Hitted!" << std::endl;
			(*it)->m_remove = true;			// 총알이 관통 못하도록.
			if(m_hp == 2)
				SoundManager::Play("Boss1Hitted");
			m_pAnimation->SetClip("Idle2");
			m_pAnimation->Play();
			return true;
		}
	}
	return false;
}

void Boss1::Attack()
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


void Boss1::AttackLoop()
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