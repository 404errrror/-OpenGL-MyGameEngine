#pragma once
#include "Global.h"
#include "Transform.h"
#include "Image.h"
#include "RigidBody2D.h"
#include "BoxCollider.h"
#include "Button.h"
#include "Line.h"
#include "ShapeAnimation.h"
#include "ColorAnimation.h"
class GameObject
{
public:
	static std::list<GameObject*> list;
	Transform& transform;
	bool m_active;
	bool m_remove;

public:
	GameObject();
	~GameObject();

	virtual void Initialize();
	virtual void Start();
	virtual void Update();
	virtual void Release();

	virtual void OnCollisionEnter2D(std::list<BoxCollider*>& colliderList);
	virtual void OnCollisionExit2D(BoxCollider* collider);
	virtual void SendEvent(std::string message, float value = 0);

	void UpdateCollision();
	void SetCollisionEnter(BoxCollider* pCollider);

	void SetName(const char* name);
	void SetTag(const char* tag);
	b2Body* SetPhysicsBody(b2Body* body);

	std::string GetName();
	const char* GetTag();
	b2Body*		GetPhysicsBody();

protected:
	bool m_isStart;

private:
	const char* m_name;
	const char* m_tag;
	bool m_isInit;

	b2Body* m_pPhysicsBody;
	std::list<BoxCollider*> m_pEnterOtherColliderList;

};

