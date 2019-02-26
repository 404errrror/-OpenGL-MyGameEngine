#pragma once
#include "Block.h"
class StartBlock :
	public Block
{
public:
	StartBlock();
	~StartBlock();

	virtual void Initialize() override;
	virtual void Destory() override;

};

