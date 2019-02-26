#pragma once
#include "Enemy.h"
class Image;
class Goei :
	public Enemy
{
public:
	Goei();
	~Goei();

	virtual void Initialize();
	virtual void Start();
	virtual void Update();
	virtual void Release();

private:
	void Die()			override;
	void Attack()		override;
	void AttackLoop()	override;

	Image* m_pImage;
};

