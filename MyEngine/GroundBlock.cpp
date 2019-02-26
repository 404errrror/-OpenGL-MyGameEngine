#include "GroundBlock.h"



GroundBlock::GroundBlock()
{
	SetName("GroundBlock");
	m_hp = 10.0f;
}


GroundBlock::~GroundBlock()
{
}


void GroundBlock::Initialize()
{
	Block::Initialize();

	m_pImage->SetSprite("DefaultBlock");
	m_pImage->SetColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
}