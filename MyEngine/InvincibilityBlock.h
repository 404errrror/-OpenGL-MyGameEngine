#pragma once
#include "Block.h"
class InvincibilityBlock :
	public Block
{
public:
	static std::list<Block*> list;
public:
	InvincibilityBlock();
	~InvincibilityBlock();

	virtual void Initialize() override;
	virtual void Release() override;
	virtual void Hitted(float damage) override;
};

