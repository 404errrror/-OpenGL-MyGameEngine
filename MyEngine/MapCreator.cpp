#include "MapCreator.h"
#include "M_Player.h"

#include "GroundBlock.h"
#include "ExplosionBlock.h"
#include "AttackItemBlock.h"
#include "RangeItemBlock.h"
#include "SpeedItemBlock.h"
#include "LaserBlock.h"
#include "LimitTrap.h"

#include "Rifle.h"
#include "Sniper.h"

MapCreator* MapCreator::instance;
#define PATTERN_NUM 5


int BlockWeight::GetWeight(Block::BlockID blockID)
{
	switch (blockID)
	{
	case Block::Empty:
		return empty;
	case Block::Ground:
		return ground;
	case Block::Explosion:
		return explosion;
	case Block::AttackItem:
		return attackItem;
	case Block::RangeItem:
		return rangeItem;
	case Block::SpeedItem:
		return speedItem;
	default:
		return -1;
	}
}

MapCreator::MapCreator()
{
	if (instance == nullptr)
	{
		instance = this;
		m_centerPosition = glm::ivec2(0, 0);
	}
	else
	{
		m_active = false;
		m_remove = true;
	}
}


MapCreator::~MapCreator()
{
}


void MapCreator::Initialize()
{
	GameObject::Initialize();

}


void MapCreator::Start()
{
	GameObject::Start();
	player = M_Player::instance;
	glm::vec3 playerPosition = player->transform.GetPosition();
	m_centerPosition = glm::ivec2((int)playerPosition.x, (int)playerPosition.y);
	GenerateBlockWeight();
	GenerateMapStartPoint();
}


void MapCreator::Update()
{
	GameObject::Update();
	glm::vec3 playerPosition = player->transform.GetPosition();
	GenerateMap(glm::ivec2((int)playerPosition.x, (int)playerPosition.y));
	RemoveGrabage();
}


void MapCreator::Release()
{
	GameObject::Release();
}


void MapCreator::RemoveGrabage()
{
	for (std::list<glm::ivec2>::iterator it = genPositionList.begin(); it != genPositionList.end(); )
	{
		if (it->y > LimitTrap::instance->transform.GetPosition().y)
			it = genPositionList.erase(it);
		else
			++it;
	}
}


void MapCreator::GenerateMap(glm::ivec2 centerPoint)
{

	glm::ivec2 genRange = m_centerPosition - centerPoint;
	int halfHeight = height * 0.6f;		// ³Ë³ËÇÏ°Ô
	int halfWidth = width * 0.6f;		// ³Ë³ËÇÏ°Ô
	int temp = 1;
	int random;

	// xÃàÀ¸·Î ¿òÁ÷¿´´Ù¸é.
	if (genRange.x > 0)
		temp = -1;
	else
		temp = 1;
	for (int x = genRange.x; x != 0; x += temp)
	{
		for (int y = centerPoint.y - halfHeight; y < centerPoint.y + halfHeight; y++)
		{
			random = Random::Range(0, 100);
			glm::ivec2 spawnPosition = glm::ivec2(m_centerPosition.x + halfWidth  * temp + x, y);
			if (random < 3)					//  ·£´ý ÆÐÅÏ »ý¼º
			{
				if (temp == -1)
					GeneratePattern(spawnPosition, Random::Range(1, PATTERN_NUM), Left);
				else
					GeneratePattern(spawnPosition, Random::Range(1, PATTERN_NUM), Right);
			}
			else if (random < 6)
			{
				if (temp == -1)
					GeneratePattern(spawnPosition, Random::Range(2, 3), Left);
				else
					GeneratePattern(spawnPosition, Random::Range(2, 3), Right);
			}
			else								// ·£´ý ºí·° »ý¼º
				GenerateRandomBlock(spawnPosition);
		}
	}

	// yÃàÀ¸·Î ¿òÁ÷¿´´Ù¸é.
	if (genRange.y > 0)
		temp = -1;
	else
		temp = 1;
	for (int y = genRange.y; y != 0; y += temp)
	{
		for (int x = centerPoint.x - halfWidth; x < centerPoint.x + halfWidth; x++)
		{
			random = Random::Range(0, 100);
			glm::ivec2 spawnPosition = glm::ivec2(x, m_centerPosition.y + halfHeight * temp + y);
			if (random < 3)					//  ·£´ý ÆÐÅÏ »ý¼º
			{
				if (temp == -1)
					GeneratePattern(spawnPosition, Random::Range(1, PATTERN_NUM), Bottom);
				else
					GeneratePattern(spawnPosition, Random::Range(1, PATTERN_NUM), Top);
			}
			else if (random < 10)
			{
				if (temp == -1)
					GeneratePattern(spawnPosition, Random::Range(2, 3), Bottom);
				else
					GeneratePattern(spawnPosition, Random::Range(2, 3), Top);
			}

			else								// ·£´ý ºí·° »ý¼º
				GenerateRandomBlock(spawnPosition);
		}
	}

	if(genRange != glm::ivec2(0))
		m_centerPosition = centerPoint;
}


void MapCreator::GenerateMapStartPoint()
{
	int halfHeight = height * 0.4f;
	int halfWidth = width * 0.5f;

	glm::vec3 playerPosition = M_Player::instance->transform.GetPosition();
	
	for(int y = -halfHeight; y < halfHeight; ++y)
		for (int x = -halfWidth; x < halfWidth; ++x)
		{
			GenerateRandomBlock(glm::ivec2(x + playerPosition.x, y + playerPosition.y));
		}
}


void MapCreator::GenerateBlock(glm::ivec2 point, Block::BlockID blockID)
{

	genPositionList.push_back(point);
	GameObject* temp;

	switch (blockID)
	{
	case Block::Ground:
		temp = new GroundBlock();
		break;
	case Block::Explosion:
		temp = new ExplosionBlock();
		break;
	case Block::AttackItem:
		temp = new AttackItemBlock();
		break;
	case Block::RangeItem:
		temp = new RangeItemBlock();
		break;
	case Block::SpeedItem:
		temp = new SpeedItemBlock();
		break;
	case Block::Laser1:
		temp = new LaserBlock();
		break;
	case Block::Laser2:
		temp = new LaserBlock();
		break;
	case Block::Laser4:
		temp = new LaserBlock();
		break;
	case Block::Empty:
		return;
	default:
		return;
	}

	temp->Initialize();
	temp->transform.SetPosition(glm::vec3(point.x, point.y, LAYER_BLOCK));


	switch (blockID)
	{
	case Block::Laser1:
		dynamic_cast<LaserBlock*>(temp)->SetLaserCount(1);
		break;
	case Block::Laser2:
		dynamic_cast<LaserBlock*>(temp)->SetLaserCount(2);
		break;
	case Block::Laser4:
		dynamic_cast<LaserBlock*>(temp)->SetLaserCount(3);
		break;
	default:
		break;
	}

}


void MapCreator::GenerateRandomBlock(glm::ivec2 point)
{
	if (point.y >= -1 || point.y > LimitTrap::instance->transform.GetPosition().y)
		return;
	for (std::list<glm::ivec2>::iterator it = genPositionList.begin(); it != genPositionList.end(); ++it)
	{
		if (point == *it)
			return;
	}

	int random = Random::Range(0, m_blockWeight[point.y * -1].allWeight - 1);
	Block::BlockID randomBlock;
	int nowWeight = 0;

	for (int i = 0; i < Block::BlockID::End; ++i)
	{
		nowWeight += m_blockWeight[point.y * -1].GetWeight((Block::BlockID)i);
		if (random < nowWeight)
		{
			randomBlock = (Block::BlockID)i;
			break;
		}
	}

	GenerateBlock(point, randomBlock);
}


void MapCreator::GenerateBlockWeight()
{
	for (int i = 0; i < 1000; ++i)
	{
		int itemWeight = 3;
		m_blockWeight[i].empty = 100;
		m_blockWeight[i].ground = 500;
		m_blockWeight[i].explosion = 10;
		m_blockWeight[i].attackItem = itemWeight;
		m_blockWeight[i].rangeItem = itemWeight;
		m_blockWeight[i].speedItem = itemWeight;

		m_blockWeight[i].allWeight = 
			m_blockWeight[i].empty +
			m_blockWeight[i].ground +
			m_blockWeight[i].explosion +
			m_blockWeight[i].attackItem +
			m_blockWeight[i].rangeItem +
			m_blockWeight[i].speedItem;
	}
}


void MapCreator::GenerateGun(glm::ivec2 point)
{
	genPositionList.push_back(point);
	int random = Random::Range(0, 100);
	if (random < 50)
	{
		Gun* temp = new Rifle();
		temp->Initialize();
		temp->transform.SetPosition(glm::vec3(point.x, point.y, LAYER_ITEM));
	}
	else
	{
		Gun* temp = new Sniper();
		temp->Initialize();
		temp->transform.SetPosition(glm::vec3(point.x, point.y, LAYER_ITEM));
	}
}


void MapCreator::GeneratePattern(glm::ivec2 point, int num, MapCreator::Direction dir)
{
	if (point.y >= -1 || point.y > LimitTrap::instance->transform.GetPosition().y)
		return;
	for (std::list<glm::ivec2>::iterator it = genPositionList.begin(); it != genPositionList.end(); ++it)
	{
		if (point == *it)
			return;
	}


	switch (num)
	{
	case 1:									// ÃÑ »ý¼º ÆÐÅÏ
	{
		switch (dir)
		{
			break;
		case MapCreator::Bottom:
			point.y -= 1;
			break;
		case MapCreator::Left:
			point.x -= 2;
			break;
		case MapCreator::Right:
		case MapCreator::Top:
			break;
		}

		// ÃÑÀÌ ¾Æ·¡·Î ¾È¶³¾îÁö°Ô.
		for (int i = 0; i < 3; ++i)
			GenerateBlock(glm::ivec2(point.x + i, point.y), Block::BlockID::Ground);

		GenerateBlock(	glm::ivec2(point.x,		point.y + 1), Block::BlockID::Empty);
		GenerateGun(	glm::ivec2(point.x + 1,	point.y + 1));
		GenerateBlock(	glm::ivec2(point.x + 2,	point.y + 1), Block::BlockID::Empty);
		break;
	}
	
	case 2:									// ºóÄ­ ÆÐÅÏ
	{
		switch (dir)
		{
			break;
		case MapCreator::Bottom:
			point.y -= 2;
			break;
		case MapCreator::Left:
			point.x -= 2;
			break;
		case MapCreator::Right:
		case MapCreator::Top:
			break;
		}

		for(int y = 0; y < 3; ++y)
			for (int x = 0; x < 3; ++x)
				GenerateBlock(glm::ivec2(point.x + x, point.y + y), Block::BlockID::Empty);
		break;
	}

	case 3:									// ºóÄ­ ÆÐÅÏ
	{
		switch (dir)
		{
			break;
		case MapCreator::Bottom:
			point.y -= 2;
			break;
		case MapCreator::Left:
			point.x -= 2;
			break;
		case MapCreator::Right:
		case MapCreator::Top:
			break;
		}

		GenerateBlock(glm::ivec2(point.x + 1, point.y), Block::BlockID::Empty);
		for (int x = 0; x < 3; ++x)
				GenerateBlock(glm::ivec2(point.x + x, point.y + 1), Block::BlockID::Empty);
		GenerateBlock(glm::ivec2(point.x + 1, point.y + 2), Block::BlockID::Empty);

		break;
	}

	case 4:
	{
		switch (dir)
		{
			break;
		case MapCreator::Bottom:
			point.y -= 2;
			break;
		case MapCreator::Left:
			point.x -= 2;
			break;
		case MapCreator::Right:
		case MapCreator::Top:
			break;
		}

		for (int y = 0; y < 3; ++y)
			for (int x = 0; x < 3; ++x)
			{
				if(x == 1 && y == 1)
					GenerateBlock(glm::ivec2(point.x + 1, point.y + 1), Block::BlockID::Laser4);
				else
					GenerateBlock(glm::ivec2(point.x + x, point.y + y), Block::BlockID::Empty);
			}
		break;
	}

	case 5:
	{
		switch (dir)
		{
			break;
		case MapCreator::Bottom:
			point.y -= 0;
			break;
		case MapCreator::Left:
			point.x -= 2;
			break;
		case MapCreator::Right:
		case MapCreator::Top:
			break;
		}

		int random = Random::Range(1, 3);

		GenerateBlock(glm::ivec2(point.x, point.y), Block::BlockID::Empty);
		GenerateBlock(glm::ivec2(point.x + 2, point.y), Block::BlockID::Empty);

		switch (random)
		{
		case 1:
			GenerateBlock(glm::ivec2(point.x + 1, point.y), Block::BlockID::Laser1);
			break;
		case 2:
			GenerateBlock(glm::ivec2(point.x + 1, point.y), Block::BlockID::Laser2);
			break;
		case 3:
			GenerateBlock(glm::ivec2(point.x + 1, point.y), Block::BlockID::Laser4);
			break;
		default:
			break;
		}
		break;

	}
	default:
		break;
	}
}
