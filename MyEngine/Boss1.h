#pragma once
#include "Enemy.h"
class Image;
class Boss1 :
	public Enemy
{
public:
	Boss1();
	~Boss1();

	virtual void Initialize();
	virtual void Start();
	virtual void Update();
	virtual void Release();

protected:
	bool HittedCheck() override;
	void Die()			override;
	void Attack()		override;
	void AttackLoop()	override;

private:
	Image* m_pImage;
};

