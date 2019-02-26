#pragma once
#include "ItemBlock.h"
class RangeItemBlock :
	public ItemBlock
{
public:
	RangeItemBlock();
	~RangeItemBlock();
	virtual void Initialize();
	virtual void OnCollisionEnter2D(std::list<BoxCollider*>& colliderList) override;

	void GetEffect();
};

