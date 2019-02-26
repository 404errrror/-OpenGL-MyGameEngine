#pragma once
#include "GameObject.h"
class GalagaNumber;
class RemainBullet :
	public GameObject
{
public:
	RemainBullet();
	~RemainBullet();

	virtual void Initialize();
	virtual void Start();
	virtual void Update();
	virtual void Release();

private:
	GalagaNumber* m_pNumber;
	GameObject* m_pIcon;
	Image* m_pIconImage;
};

