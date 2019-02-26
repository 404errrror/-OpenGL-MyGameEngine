#pragma once
#include "GameObject.h"
class GalagaNumber;

class LimitTrap :
	public GameObject
{
public:
	static LimitTrap* instance;
public:
	LimitTrap();
	~LimitTrap();

	virtual void Initialize();
	virtual void Start();
	virtual void Update();
	virtual void Release();

	void TrapMark();
private:
	float m_speed;
	Image* m_pImage;
	GalagaNumber* m_pDistance;
	Image* m_pMarkImage;
};

