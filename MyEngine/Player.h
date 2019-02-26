#pragma once
#include "GameObject.h"

#define ATTACK_DELAY 0.5f

class RigidBody2D;
class Animation;

class Player :
	public GameObject
{
public:
	static Player* instance;
	static int life;
	static int bulletCount;

public:
	Player();
	~Player();

	void Initialize()		override;
	void Start()			override;
	void Update()			override;
	void Release()			override;


	void Move();
	void Attack();
	void Die();
	void Respawn();

	void InfinityBullet();
private:
	bool m_isDie;
	bool m_ignoreAttack;
	float m_dieCoolTime;
	int m_bulletLimit;

	RigidBody2D* m_pRigid;
	Animation* m_pAnimation;
};