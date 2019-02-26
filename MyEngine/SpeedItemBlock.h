#pragma once
#include "ItemBlock.h"
class SpeedItemBlock :
	public ItemBlock
{
public:
	SpeedItemBlock();
	~SpeedItemBlock();

	virtual void Initialize();
	virtual void OnCollisionEnter2D(std::list<BoxCollider*>& colliderList) override;

	void GetEffect();
};

