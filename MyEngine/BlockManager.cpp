#include "BlockManager.h"
#include "M_Player.h"
#include "CameraC.h"
#include "LimitTrap.h"

std::list<Block*> BlockManager::activeList;
std::list<Block*> BlockManager::inactiveList;
BlockManager* BlockManager::instance;

#define BLOCK_WIDTH_RANGE 14
#define BLOCK_HEIGHT_RANGE 10

BlockManager::BlockManager()
{
	if (instance == nullptr)
	{
		instance = this;
	}
	else
	{
		m_remove = true;
		m_active = false;
	}
}


BlockManager::~BlockManager()
{
}

void BlockManager::Initialize()
{
	GameObject::Initialize();
}


void BlockManager::Start()
{
	GameObject::Start();


}


void BlockManager::Update()
{
	GameObject::Update();

	//BlockCulling();
}


void BlockManager::Release()
{
	GameObject::Release();
	activeList.clear();
	inactiveList.clear();
	if (instance == this)
		instance = nullptr;
}


void BlockManager::BlockCulling()
{
	// 비활성화
	for (std::list<Block*>::iterator it = activeList.begin(); it != activeList.end();)
	{
		float distanceX = (*it)->transform.GetPosition().x + CameraC::main->gameObject.transform.GetPosition().x;
		float distanceY = (*it)->transform.GetPosition().y + CameraC::main->gameObject.transform.GetPosition().y;

		if ((*it)->GetName() == "LaserBlock")
		{
			//if (
			//	distanceX > BLOCK_WIDTH_RANGE * 4 ||
			//	distanceX < -BLOCK_WIDTH_RANGE * 4||
			//	distanceY > BLOCK_HEIGHT_RANGE * 4||
			//	distanceY < -BLOCK_HEIGHT_RANGE * 4
			//	)
			//{
			//	(*it)->m_active = false;
			//	inactiveList.push_back(*it);
			//	it = activeList.erase(it);
			//}
			//else
			//{
				++it;
			//}
		}
		else if (
			distanceX > BLOCK_WIDTH_RANGE ||
			distanceX < -BLOCK_WIDTH_RANGE ||
			distanceY > BLOCK_HEIGHT_RANGE ||
			distanceY < -BLOCK_HEIGHT_RANGE
			)
		{
			(*it)->m_active = false;
			inactiveList.push_back(*it);
			it = activeList.erase(it);
		}
		else
		{
			++it;
		}
	}

	// 활성화
	for (std::list<Block*>::iterator it = inactiveList.begin(); it != inactiveList.end();)
	{
		if ((*it)->transform.GetPosition().y > LimitTrap::instance->transform.GetPosition().y)
		{
			(*it)->m_remove = true;
			it = inactiveList.erase(it);
			continue;
		}

		float distanceX = (*it)->transform.GetPosition().x + CameraC::main->gameObject.transform.GetPosition().x;
		float distanceY = (*it)->transform.GetPosition().y + CameraC::main->gameObject.transform.GetPosition().y;

		if ((*it)->GetName() == "LaserBlock")
		{
			if (
				distanceX < BLOCK_WIDTH_RANGE * 4 &&
				distanceX > -BLOCK_WIDTH_RANGE * 4 &&
				distanceY < BLOCK_HEIGHT_RANGE * 4 &&
				distanceY > -BLOCK_HEIGHT_RANGE * 4
				)
			{
				(*it)->m_active = true;
				activeList.push_back(*it);
				it = inactiveList.erase(it);
			}
			else
				++it;
		}
		else
		{
			if (
				distanceX < BLOCK_WIDTH_RANGE &&
				distanceX > -BLOCK_WIDTH_RANGE &&
				distanceY < BLOCK_HEIGHT_RANGE &&
				distanceY > -BLOCK_HEIGHT_RANGE
				)
			{
				(*it)->m_active = true;
				activeList.push_back(*it);
				it = inactiveList.erase(it);
			}
			else
				++it;
		}
	}
}