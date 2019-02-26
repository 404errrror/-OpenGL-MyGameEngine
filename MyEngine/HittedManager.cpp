#include "HittedManager.h"
#include "CameraC.h"
#include "BoxCollider.h"
#include "GameObject.h"
#include "LimitTrap.h"

std::list<BoxCollider*> HittedManager::activeList;
std::list<BoxCollider*> HittedManager::inactiveList;

#define BLOCK_WIDTH_RANGE 14
#define BLOCK_HEIGHT_RANGE 10


HittedManager::HittedManager()
{
}


HittedManager::~HittedManager()
{
}


void HittedManager::Release()
{
	activeList.clear();
}


void HittedManager::Update()
{
	Culling();
}


void HittedManager::Culling()
{
	// 비활성화
	for (std::list<BoxCollider*>::iterator it = activeList.begin(); it != activeList.end();)
	{
		float distanceX = (*it)->gameObject.transform.GetPosition().x + CameraC::main->gameObject.transform.GetPosition().x;
		float distanceY = (*it)->gameObject.transform.GetPosition().y + CameraC::main->gameObject.transform.GetPosition().y;

		if ((*it)->gameObject.GetName() == "LaserBlock")
		{
			if (
				distanceX > BLOCK_WIDTH_RANGE * 2 ||
				distanceX < -BLOCK_WIDTH_RANGE * 2||
				distanceY > BLOCK_HEIGHT_RANGE * 2||
				distanceY < -BLOCK_HEIGHT_RANGE * 2
				)
			{
				(*it)->gameObject.m_active = false;
				inactiveList.push_back(*it);
				it = activeList.erase(it);
			}
			else
			{
			++it;
			}
		}
		else if (
			distanceX > BLOCK_WIDTH_RANGE ||
			distanceX < -BLOCK_WIDTH_RANGE ||
			distanceY > BLOCK_HEIGHT_RANGE ||
			distanceY < -BLOCK_HEIGHT_RANGE
			)
		{
			(*it)->gameObject.m_active = false;
			inactiveList.push_back(*it);
			it = activeList.erase(it);
		}
		else
			++it;
	}

	// 활성화
	for (std::list<BoxCollider*>::iterator it = inactiveList.begin(); it != inactiveList.end();)
	{
		if ((*it)->gameObject.transform.GetPosition().y > LimitTrap::instance->transform.GetPosition().y)
		{
			(*it)->gameObject.m_remove = true;
			it = inactiveList.erase(it);
			continue;
		}

		float distanceX = (*it)->gameObject.transform.GetPosition().x + CameraC::main->gameObject.transform.GetPosition().x;
		float distanceY = (*it)->gameObject.transform.GetPosition().y + CameraC::main->gameObject.transform.GetPosition().y;

		if ((*it)->gameObject.GetName() == "LaserBlock")
		{
			if (
				distanceX < BLOCK_WIDTH_RANGE * 2 &&
				distanceX > -BLOCK_WIDTH_RANGE * 2 &&
				distanceY < BLOCK_HEIGHT_RANGE * 2 &&
				distanceY > -BLOCK_HEIGHT_RANGE * 2
				)
			{
				(*it)->gameObject.m_active = true;
				activeList.push_back(*it);
				it = inactiveList.erase(it);
			}
			else
			{
				++it;
			}
		}
		else if (
			distanceX < BLOCK_WIDTH_RANGE &&
			distanceX > -BLOCK_WIDTH_RANGE &&
			distanceY < BLOCK_HEIGHT_RANGE &&
			distanceY > -BLOCK_HEIGHT_RANGE
			)
		{
			(*it)->gameObject.m_active = true;
			activeList.push_back(*it);
			it = inactiveList.erase(it);
		}
		else
			++it;
	}
}


void HittedManager::Add(BoxCollider* pCollider)
{
	activeList.push_back(pCollider);
}


void HittedManager::Remove(BoxCollider* pCollider)
{
	for (std::list<BoxCollider*>::iterator it = activeList.begin(); it != activeList.end(); ++it)
	{
		if (*it == pCollider)
		{
			activeList.erase(it);
			return;
		}
	}

	for (std::list<BoxCollider*>::iterator it = inactiveList.begin(); it != inactiveList.end(); ++it)
	{
		if (*it == pCollider)
		{
			inactiveList.erase(it);
			return;
		}
	}
}