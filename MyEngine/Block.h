#pragma once
#include "GameObject.h"

class Block :
	public GameObject
{
public:
	enum BlockID
	{
		Empty, Ground, Explosion, AttackItem, RangeItem, SpeedItem, End, Laser1, Laser2, Laser4
	};
public:
	Block();
	~Block();

	virtual void Initialize() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void Release() override;
	virtual void SendEvent(std::string message, float value = 0.0f) override;

	virtual void Hitted(float damage);
	virtual void Destory();
	virtual void DestoryEffect();

protected:
	Image* m_pImage;
	BoxCollider* m_pCollider;
	ColorAnimation* m_pHittedAni;
	float m_hp;
};

