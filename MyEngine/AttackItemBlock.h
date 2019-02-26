#pragma once
#include "ItemBlock.h"
class AttackItemBlock :
	public ItemBlock
{
public:
	AttackItemBlock();
	~AttackItemBlock();

	virtual void Initialize();
	virtual void OnCollisionEnter2D(std::list<BoxCollider*>& colliderList) override;

	void GetEffect();
};

