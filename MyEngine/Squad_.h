#pragma once
#include "GameObject.h"
#include "Global.h"
#include "MovePattern.h"

class Enemy;
class Squad_ :
	public GameObject
{
public:
	std::list<Enemy*> m_pEnemyList;

public:
	Squad_(MovePattern movePattern);
	~Squad_();

	void Initialize()	override;
	void Start()		override;
	void Update()		override;
	void Release()		override;

	void AddEnemy(Enemy* pEnemy);
	void ReleaseObject(Enemy* pEnemy);
	void SetDelayTime(float time);
	void SetSpawnPoint(glm::vec3 point);

private:
	MovePattern m_pPattern;
	GameObject* m_pNowEnemy;
	float		m_delayTime;
	glm::vec3	m_spawnPoint;

private:
	void ActiveObject();
};

