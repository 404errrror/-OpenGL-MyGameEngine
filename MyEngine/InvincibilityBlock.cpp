#include "InvincibilityBlock.h"

std::list<Block*> InvincibilityBlock::list;

InvincibilityBlock::InvincibilityBlock()
{
	SetName("InvincibilityBlock");
	list.push_back(this);
}


InvincibilityBlock::~InvincibilityBlock()
{
}


void InvincibilityBlock::Initialize()
{
	Block::Initialize();

	m_pImage->SetSprite("InvincibilityBlock");
	m_pImage->SetColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
}


void InvincibilityBlock::Hitted(float damage)
{
	return;
}


void InvincibilityBlock::Release()
{
	for (std::list<Block*>::iterator it = list.begin(); it != list.end(); ++it)
	{
		if (*it == this)
		{
			list.erase(it);
			break;
		}
	}

	Block::Release();
}