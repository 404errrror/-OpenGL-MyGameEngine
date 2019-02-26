#include "Enemy.h"
#include "Animation.h"
#include "BoxCollider.h"
#include "Bullet.h"
#include "Squad.h"

#include "GalagaUi.h"
#include "Stage.h"

int Enemy::count;

Enemy::Enemy()
{
	m_score = 10;
	m_hp = 1;
	m_squadIndex = -1;
	m_isFly = true;
	m_stop = false;
	m_speed = 1.0f;
	m_stopTime = 0;
	m_endPosition = glm::vec3(0, 0,0);

	m_pAnimation = nullptr;
	m_pCollider = nullptr;
	m_pSquad = nullptr;
	m_pPattern = nullptr;
	m_pEndPattern = nullptr;
	++count;

	m_isPlayBgm = false;
}


Enemy::~Enemy()
{
}


void Enemy::Initialize()
{
	GameObject::Initialize();

	m_pAnimation = transform.AddComponent<Animation>();
	m_pCollider = transform.AddComponent<BoxCollider>();
	
	transform.SetScale(glm::vec3(0.1f));

	m_pAnimation->AddClip("Die");
	m_pAnimation->SetFrame("Die", "EnemyDie_0");
	m_pAnimation->SetFrame("Die", "EnemyDie_1");
	m_pAnimation->SetFrame("Die", "EnemyDie_2");
	m_pAnimation->SetFrame("Die", "EnemyDie_3");
	m_pAnimation->SetFrame("Die", "EnemyDie_4");

}


void Enemy::Start()
{
	GameObject::Start();
}


void Enemy::Update()
{
	GameObject::Update();

	if (m_stopTime > 0.0f)
	{
		m_stopTime -= Time::GetDeltaTime();
		if (m_stopTime <= 0.0f)
		{
			SoundManager::Play("EnemyFly");
			m_stop = false;
			m_stopTime = 0.0f;
		}
	}

	if (m_hp > 0 && HittedCheck())
		--m_hp;

	if (m_hp <= 0)
		Die();

	// switch 문으로 1 - 2 - 3 돌아가면서 하면 괜찮을거같음.

	if (m_hp > 0 && m_stop == false)			// 살아있다면
	{
		transform.Translate(glm::vec3(0, Time::GetDeltaTime() * m_speed * (0.7f + ((float)Stage::m_nowStage * 0.3f)), 0));

		if (m_pPattern != nullptr && m_pPattern->IsEnd() == false)	// 이동 패턴이 끝나지 않았다면.
		{
			m_pPattern->Update();
			transform.SetRotation(m_pPattern->GetRotateData());
		}
		else								// 이동 패턴이 끝났다면
			if (m_pEndPattern != nullptr && m_pEndPattern->IsArrive() == false)	// 자리로 이동하는 패턴실행. 한번이라도 도착이 완료되었다면 그 이후엔 실행안됨.
			{
				m_pEndPattern->Update();
				transform.LookAt2D(m_pEndPattern->GetEndPosition());

				if (glm::distance(transform.GetPosition(), m_pEndPattern->GetEndPosition()) < 0.01f)	// 자리에 도착했다면
				{
					m_pEndPattern->Arrive(true);
					transform.SetRotation(glm::vec3(0, 0, 0));
					m_pPattern->Clear();
					transform.SetPosition(m_pEndPattern->GetEndPosition());
					BaseAttack();		// 공격패턴 실행
				}
			}
			else				// 공격 패턴이 끝났다면
			{
				AttackLoop();	// 공격 루프 진행.
			}

		if (transform.GetPosition().y <= -1.3f)
			transform.SetPosition(glm::vec3(transform.GetPosition().x, 1.2f, 0.0f));
		else if (transform.GetPosition().y >= 1.5f)
			transform.SetPosition(glm::vec3(transform.GetPosition().x, -1.2f, 0.0f));
	}

}


void Enemy::Release()
{
	GameObject::Release();
	delete m_pPattern;

	--count;

	if (m_pSquad != nullptr)
	{
		for (std::list<Enemy*>::iterator it = m_pSquad->m_pEnemyList.begin(); it != m_pSquad->m_pEnemyList.end(); ++it)
		{
			if (*it == this)
			{
				m_pSquad->m_pEnemyList.erase(it);
				return;
			}
		}
	}
}


void Enemy::Attack()
{

}


void Enemy::AttackLoop()
{

}


void Enemy::BaseAttack()
{
	if (m_pPattern != nullptr)
	{
		WaitSeconds(Random::Range(10,20));
		Attack();
	}
}


/// <summary>
/// 지정한 시간만큼 움직임을 멈춥니다.
/// </summary>
void Enemy::WaitSeconds(float seconds)
{
	m_stopTime = seconds;
	m_stop = true;
}

//
//void Enemy::SetSquad(Squad* squad)
//{
//	m_pSquad = squad;
//}
//
//
//void Enemy::SetSquadIndex(int index)
//{
//	m_squadIndex = index;
//}


void Enemy::SetPattern(MovePattern& movePattern)
{
	m_pPattern = new MovePattern(movePattern);
}


void Enemy::SetEndPattern(EndPattern& endPattern)
{
	m_pEndPattern = new EndPattern(endPattern);
}


int Enemy::GetSquadIndex()
{
	return m_squadIndex;
}


void Enemy::Die()
{
	if (m_pAnimation->GetClipKey() != "Die")			// 총알 처음 맞고 애니메이션 셋팅할 때.
	{
		m_pAnimation->SetClip("Die");
		m_pAnimation->Play();
		m_pAnimation->SetLoop(false);
		transform.SetScale(glm::vec3(0.15f, 0.15f, 0.15f));
		//transform.SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));
		m_pAnimation->SetFrameDelay(0.1f);
		m_pCollider->m_enable = false;
		if(m_stop)
			*GalagaUi::score += m_score;
		else
			*GalagaUi::score += m_score * 2;

	}
	else
	{

		if (m_pAnimation->IsPlay() == false)
			m_remove = true;
	}
}


bool Enemy::HittedCheck()
{
	for (std::list<Bullet*>::iterator it = Bullet::myList.begin(); it != Bullet::myList.end(); ++it)
	{
		if (m_pCollider->CollisionCheck(glm::vec2((*it)->transform.GetPosition())) &&
			(*it)->m_remove == false
			)
		{
			std::cout << "Hitted!" << std::endl;
			(*it)->m_remove = true;			// 총알이 관통 못하도록.
			return true;
		}
	}
	return false;
}