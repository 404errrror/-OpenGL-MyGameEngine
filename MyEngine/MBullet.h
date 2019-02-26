#pragma once
#include "GameObject.h"
class MBullet :
	public GameObject
{
public:
	MBullet();
	~MBullet();

	//virtual void Initialize() override {}
	//virtual void Start() override {}
	//virtual void Update() override {}
	//virtual void Release() override {}

	//virtual void OnCollisionEnter2D(BoxCollider* collider) override {}

	virtual void Shoot(glm::vec2 startPoint, glm::vec2 endPoint) {}

	int m_damage;
};

