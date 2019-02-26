#include "Squad_.h"
#include "Jako.h"
#include "Enemy.h"

Squad_::Squad_(MovePattern movePattern)
{
	m_pPattern = movePattern;
	m_pNowEnemy = nullptr;
	m_delayTime = 0;
	m_spawnPoint = glm::vec3(0);
}


Squad_::~Squad_()
{
}


void Squad_::Initialize()
{
	GameObject::Initialize();

}


void Squad_::Start()
{
	GameObject::Start();
}


void Squad_::Update()
{
	GameObject::Update();

	m_delayTime -= Time::GetDeltaTime();

	if (m_delayTime <= 0)
	{
		if (m_pNowEnemy == nullptr )
		{
			if (m_pEnemyList.empty() == false)
			{
				m_pNowEnemy = m_pEnemyList.front();
				m_pEnemyList.pop_front();
				m_pNowEnemy->m_active = true;
				m_pNowEnemy->transform.SetPosition(m_spawnPoint);
			}
		}

		else if (glm::distance(m_pNowEnemy->transform.GetPosition(), m_spawnPoint) >= 0.1f)
			ActiveObject();
	}
}


void Squad_::Release()
{
	GameObject::Release();

	for (std::list<Enemy*>::iterator it = m_pEnemyList.begin(); it != m_pEnemyList.end();)
	{
		(*it)->m_remove = true;
		it = m_pEnemyList.erase(it);
	}
}


void Squad_::AddEnemy(Enemy* pEnemy)
{
	pEnemy->Initialize();
	pEnemy->m_active = false;
	m_pEnemyList.push_back(pEnemy);
	pEnemy->SetPattern(m_pPattern);
}


// 없애도 될듯. Enemy측에서 release할때 list에 접근해서 erase하고있음.
void Squad_::ReleaseObject(Enemy* pEnemy)
{
	for (std::list<Enemy*>::iterator it = m_pEnemyList.begin(); it != m_pEnemyList.end(); ++it)
	{
		if (*it == pEnemy)
		{
			m_pEnemyList.erase(it);
			return;
		}
	}
}


void Squad_::SetDelayTime(float time)
{
	m_delayTime = time;
}


void Squad_::SetSpawnPoint(glm::vec3 point)
{
	m_spawnPoint = point;
}


void Squad_::ActiveObject()
{
	if (m_pEnemyList.empty())
	{
		m_remove = true;
	}
	else
	{
		m_pNowEnemy = m_pEnemyList.front();
		m_pEnemyList.pop_front();
		m_pNowEnemy->m_active = true;
		m_pNowEnemy->transform.SetPosition(m_spawnPoint);
	}
}