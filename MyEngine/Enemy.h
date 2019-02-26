#pragma once
#include "Global.h"
#include "GameObject.h"
#include "MovePattern.h"
#include "EndPattern.h"

class Animation;
class BoxCollider;
class Squad;
class MovePattern;
class EndPattern;

class Enemy :
	public GameObject
{
public:
	static int count;
public:
	Enemy();
	~Enemy();

	virtual void Initialize();
	virtual void Start();
	virtual void Update();
	virtual void Release();


			void WaitSeconds(float seconds);
	//virtual void CollisionCheck(glm::vec2);

	//void SetSquad(Squad* squad);
	//void SetSquadIndex(int index);
	void SetPattern(MovePattern& movePattern);
	void SetEndPattern(EndPattern& endPattern);

	int GetSquadIndex();

protected:
	int			m_score;
	int			m_hp;
	int			m_squadIndex;
	bool		m_isFly;
	bool		m_stop;
	bool		m_isPlayBgm;
	float		m_speed;
	float		m_stopTime;
	glm::vec3	m_endPosition;

	Animation*		m_pAnimation;
	BoxCollider*	m_pCollider;
	Squad*			m_pSquad;
	MovePattern*	m_pPattern;
	EndPattern*		m_pEndPattern;
protected:
	virtual void Die();
	virtual void Attack();
	virtual void AttackLoop();
	virtual bool HittedCheck();
	void BaseAttack();
};

