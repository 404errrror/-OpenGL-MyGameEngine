#include "SkinBlock.h"
#include "M_Player.h"


SkinBlock::SkinBlock()
{
	SetName("SkinBlock");
}


SkinBlock::~SkinBlock()
{
}


void SkinBlock::Initialize()
{
	Block::Initialize();
	m_pImage->SetSahder("AddColor");
	m_pImage->SetColor(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	m_pImage->SetSprite("HeroesSkin");
}


void SkinBlock::Hitted(float damage)
{
	M_Player::instance->SetSkin(m_spriteKey.c_str());
}


void SkinBlock::SetSkin(const char* spriteKey)
{
	m_pImage->SetSprite(spriteKey);
	m_spriteKey = spriteKey;
}