#include "Squad.h"
#include "Jako.h"


Squad::Squad()
{
	m_index = -1;
}


Squad::~Squad()
{
}


void Squad::Initialize()
{
	GameObject::Initialize();

}


void Squad::Start()
{
	GameObject::Start();
	AddEnemy(new Jako());
	AddEnemy(new Jako());
	AddEnemy(new Jako());
}


void Squad::Update()
{
	GameObject::Update();

	Test();
	for (int i = 1; i <= m_index; ++i)
	{
		m_pGameObject[i]->transform.LookAt2D(m_pGameObject[i-1]->transform.GetPosition());
	}
	EnemyUpdate();

		for (int i = 0; i <= m_index; ++i)
		m_pGameObject[i]->transform.Translate(glm::vec3(0, Time::GetDeltaTime() * 0.5f, 0));

}


void Squad::Release()
{
	GameObject::Release();

	for (std::list<Enemy*>::iterator it = m_pEnemyList.begin(); it != m_pEnemyList.end();)
	{
		(*it)->SetSquad(nullptr);
		(*it)->m_remove = true;
		it = m_pEnemyList.erase(it);
	}

	for (std::vector<GameObject*>::iterator it = m_pGameObject.begin(); it != m_pGameObject.end();)
	{
		(*it)->m_remove = true;
		it = m_pGameObject.erase(it);
	}
}


void Squad::AddEnemy(Enemy* pEnemy)
{
	pEnemy->Initialize();

	++m_index;
	pEnemy->SetSquad(this);
	pEnemy->SetSquadIndex(m_index);

	m_pEnemyList.push_back(pEnemy);
	m_pGameObject.push_back(new GameObject());
	m_pPosition.push_back(new glm::vec3(0));

	m_pPosition[m_index]->y -= m_index * 0.1f;
	m_pGameObject[m_index]->transform.Translate(glm::vec3(0, -m_index * 0.1f, 0));
	//pEnemy->transform.SetPosition(*m_pPosition[m_index]);
	pEnemy->transform.SetPosition(m_pGameObject[m_index]->transform.GetPosition());
}


// 없애도 될듯. Enemy측에서 release할때 list에 접근해서 erase하고있음.
void Squad::ReleaseObject(Enemy* pEnemy)
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


void Squad::EnemyUpdate()
{
	for (std::list<Enemy*>::iterator it = m_pEnemyList.begin(); it != m_pEnemyList.end(); ++it)
	{
		int index = (*it)->GetSquadIndex();
		(*it)->transform.SetRotation(
			m_pGameObject[index]->transform.GetRotation()
		);
		(*it)->transform.SetPosition(m_pGameObject[index]->transform.GetPosition());
	}
}


void Squad::Test()
{
	if (InputManager::IsKeyDown(GLFW_KEY_UP))
		m_pGameObject[0]->transform.Translate(glm::vec3(0, Time::GetDeltaTime() * 0.5f, 0));
	if (InputManager::IsKeyDown(GLFW_KEY_DOWN))
		m_pGameObject[0]->transform.Translate(glm::vec3(0, -Time::GetDeltaTime() * 0.5f, 0));
	if (InputManager::IsKeyDown(GLFW_KEY_RIGHT))
		m_pGameObject[0]->transform.Translate(glm::vec3(Time::GetDeltaTime() * 0.5f, 0, 0));
	if (InputManager::IsKeyDown(GLFW_KEY_LEFT))
		m_pGameObject[0]->transform.Translate(glm::vec3(-Time::GetDeltaTime() * 0.5f, 0, 0));
	if (InputManager::IsKeyDown(GLFW_KEY_Z))
		m_pGameObject[0]->transform.Rotate(glm::vec3(0, 0, -Time::GetDeltaTime() * 100.0f));
	if (InputManager::IsKeyDown(GLFW_KEY_X))
		m_pGameObject[0]->transform.Rotate(glm::vec3(0, 0, Time::GetDeltaTime() * 100.0f));
}