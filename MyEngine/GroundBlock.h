#pragma once
#include "Block.h"
class GroundBlock :
	public Block
{
public:
	GroundBlock();
	~GroundBlock();

	virtual void Initialize() override;
};