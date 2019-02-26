#include "SpeedItemBlock.h"
#include "ItemBlockTxtEffect.h"



SpeedItemBlock::SpeedItemBlock()
{
}


SpeedItemBlock::~SpeedItemBlock()
{
}


void SpeedItemBlock::Initialize()
{
	ItemBlock::Initialize();
	m_pImage->SetSprite("SpeedItemBlock");
}


void SpeedItemBlock::OnCollisionEnter2D(std::list<BoxCollider*>& colliderList)
{
	for (std::list<BoxCollider*>::iterator it = colliderList.begin(); it != colliderList.end(); ++it)
	{
		if ((*it)->gameObject.GetName() == "Player")
		{
			(*it)->gameObject.SendEvent("SpeedIncrease", 0.1f);
			SoundManager::Play("GetItem");
			GetEffect();
		}
	}
}


void SpeedItemBlock::GetEffect()
{
	m_remove = true;
	ItemBlockTxtEffect* m_pTxtEffect = new ItemBlockTxtEffect();
	m_pTxtEffect->Initialize();
	m_pTxtEffect->SetSprite("SpeedItemBlockTxt");
}