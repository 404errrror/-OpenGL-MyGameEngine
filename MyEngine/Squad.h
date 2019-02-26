#pragma once
#include "GameObject.h"
#include "Global.h"

class Enemy;
class Squad :
	public GameObject
{
public:
	std::list<Enemy*> m_pEnemyList;
	std::vector<glm::vec3*> m_pPosition;
	std::vector<GameObject*> m_pGameObject;
	
public:
	Squad();
	~Squad();

	void Initialize()	override;
	void Start()		override;
	void Update()		override;
	void Release()		override;

	void AddEnemy(Enemy* pEnemy);
	void ReleaseObject(Enemy* pEnemy);

private:
	int m_index;

private:
	void EnemyUpdate();
	void Test();
};

