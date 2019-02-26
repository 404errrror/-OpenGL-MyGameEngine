#pragma once
#include "Enemy.h"
class Image;
class Jako :
	public Enemy
{
public:
	Jako();
	~Jako();

	virtual void Initialize();
	virtual void Start();
	virtual void Update();
	virtual void Release();


protected:
	void Die()			override;
	void Attack()		override;
	void AttackLoop()	override;
private:
	Image* m_pImage;
};

