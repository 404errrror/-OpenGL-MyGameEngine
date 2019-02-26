#pragma once
#include "GameObject.h"
#include "Global.h"
#include "DefaultGun.h"

class Item;
class M_Player :
	public GameObject
{
public:
	static M_Player* instance;
public:
	M_Player();
	~M_Player();

	virtual void Initialize();
	virtual void Start();
	virtual void Update();
	virtual void Release();
	virtual void SendEvent(std::string message, float value = 0);

	// 아이템 관련
	void GetItem(Item* pItem);
	void AttachDefaultGun();

	// 능력치 관련
	void RangeIncrease(float persent);
	void AttackIncrease(float persent);
	void SpeedIncrease(float persent);
	float GetRange();
	float GetAttack();
	float GetSpeed();
	Gun* GetHandGun();

	void SetSkin(const char* spriteKey);

	void Die();
private:
	void Move();
	void JumpCheck();
	//void QuitSlot();
private:
	Image* m_pImage;
	RigidBody2D* m_pRigid;
	BoxCollider* m_pColl;
	ColorAnimation* m_pColorAni;
	ShapeAnimation* m_pShapeAni;

	Item* m_pHandItem;
	DefaultGun* m_pDefaultGun;
	GameObject* m_pHand;
	//Inventory* m_inventory;

	float m_range;
	float m_attack;
	float m_speed;

	bool m_isDie;
	bool m_isGameOverPlay;
	bool m_isJump;
};

