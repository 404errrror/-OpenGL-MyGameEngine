#pragma once
#include "Gun.h"
class Sniper :
	public Gun
{
public:
	Sniper();
	~Sniper();

	virtual void Initialize()	override;
	virtual void LeftPress() override;
};

