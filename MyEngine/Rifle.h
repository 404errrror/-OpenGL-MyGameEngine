#pragma once
#include "Gun.h"
class Rifle :
	public Gun
{
public:
	Rifle();
	~Rifle();

	virtual void Initialize()	override;
	virtual void LeftPressing() override;
};

