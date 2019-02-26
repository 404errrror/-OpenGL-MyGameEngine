#include "AttackItemBlock.h"
#include "ItemBlockTxtEffect.h"


AttackItemBlock::AttackItemBlock()
{
}


AttackItemBlock::~AttackItemBlock()
{
}


void AttackItemBlock::Initialize()
{
	ItemBlock::Initialize();
	m_pImage->SetSprite("AttackItemBlock");
}


void AttackItemBlock::OnCollisionEnter2D(std::list<BoxCollider*>& colliderList)
{
	for (std::list<BoxCollider*>::iterator it = colliderList.begin(); it != colliderList.end(); ++it)
	{
		if ((*it)->gameObject.GetName() == "Player" && m_remove == false)
		{
			(*it)->gameObject.SendEvent("AttackIncrease", 0.2f);
			SoundManager::Play("GetItem");
			GetEffect();
		}
	}
}


void AttackItemBlock::GetEffect()
{
	m_remove = true;
	ItemBlockTxtEffect* m_pTxtEffect = new ItemBlockTxtEffect();
	m_pTxtEffect->Initialize();
	m_pTxtEffect->SetSprite("AttackItemBlockTxt");
}