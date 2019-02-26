#pragma once
#include "Component.h"
#include "Global.h"

class BoxCollider;

class RigidBody2D :
	public Component
{
public:
	static std::list<RigidBody2D*> list;
public:
	RigidBody2D(GameObject& gameObject);
	~RigidBody2D();

	void Initialize()	override;
	void Update()		override;
	void Release()		override;

	void SetTrigger(bool isTrigger);
	void SetCollider(BoxCollider* boxCollider);
	void SetGravity(bool useGravity);
	void SetVelocity(glm::vec2 velocity);

	bool IsTrigger();
	bool IsCollision(glm::vec2 point);
	bool IsCollision(BoxCollider boxColl);

	BoxCollider* GetOtherCollider();
	glm::vec2 GetVelocity();

	void FreezeRotation(bool freeze);

private:
	void CollisionPhysics();
	void OldCode();
private:
	BoxCollider* m_pColl;
	BoxCollider* m_pOtherColl;
	b2Body* m_body;
	glm::vec3 velocity;
	bool m_isTrigger;
	bool m_useGravity;

};

