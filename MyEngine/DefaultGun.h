#pragma once
#include "Gun.h"
class DefaultGun :
	public Gun
{
public:
	DefaultGun();
	~DefaultGun();

	virtual void Initialize()	override;
	virtual void LeftPress()		override;
	virtual void Release() override;
 };

