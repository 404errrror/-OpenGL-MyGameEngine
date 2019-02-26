#pragma once
#include "Item.h"
#include "HittedManager.h"
class Gun :
	public Item
{
public:
	enum GunType
	{
		Rifle, Sniper
	};
public:
	Gun();
	~Gun();

	virtual void Initialize()	override;
	virtual void Start()		override;
	virtual void Update()		override;
	virtual void SendEvent(std::string message, float value) override;
	virtual void Release()		override;

	virtual void HandUpdate()	override;

	int GetBulletCount();
protected:
	float m_distance;
	int m_bulletCount;
	float m_delay;
	float m_damage;
	bool m_infinityBullet;
};

