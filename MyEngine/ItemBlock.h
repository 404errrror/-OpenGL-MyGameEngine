#pragma once
#include "Block.h"
class ItemBlock :
	public Block
{
public:
	ItemBlock();
	~ItemBlock();

	virtual void Initialize() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void Release() override;

protected:
	RigidBody2D* m_pRigid;
};

