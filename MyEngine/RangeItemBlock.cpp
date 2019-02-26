#include "RangeItemBlock.h"
#include "ItemBlockTxtEffect.h"


RangeItemBlock::RangeItemBlock()
{
	SetName("RangeItemBlock");
}


RangeItemBlock::~RangeItemBlock()
{
}


void RangeItemBlock::Initialize()
{
	ItemBlock::Initialize();
	m_pImage->SetSprite("RangeItemBlock");
}


void RangeItemBlock::OnCollisionEnter2D(std::list<BoxCollider*>& colliderList)
{
	for (std::list<BoxCollider*>::iterator it = colliderList.begin(); it != colliderList.end(); ++it)
	{
		if ((*it)->gameObject.GetName() == "Player")
		{
			(*it)->gameObject.SendEvent("RangeIncrease", 0.2f);
			SoundManager::Play("GetItem");
			GetEffect();
		}
	}
}


void RangeItemBlock::GetEffect()
{
	m_remove = true;
	ItemBlockTxtEffect* m_pTxtEffect = new ItemBlockTxtEffect();
	m_pTxtEffect->Initialize();
	m_pTxtEffect->SetSprite("RangeItemBlockTxt");
}