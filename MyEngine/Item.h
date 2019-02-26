#pragma once
#include "GameObject.h"
#include "Global.h"
class Item :
	public GameObject
{
public:
	Item();
	~Item();

	virtual void Initialize()	override;
	virtual void Start()		override;
	virtual void Update()		override;
	virtual void Release()		override;

	virtual void OnCollisionEnter2D(std::list<BoxCollider*>& colliderList) override;
	virtual void OnCollisionExit2D(BoxCollider* coll) override;

	virtual void HandUpdate() {}
	virtual void LeftPress() {}
	virtual void LeftPressing() {}
	virtual void LeftUp() {}
	virtual void RightPress() {}
	virtual void RightPressing() {}
	virtual void RightUp() {}

	virtual void Hitted(float value);
	virtual void Destroy();


	int GetItemId();

	void Attacth(Transform& transform);
	void Detatch();
	void Throw(glm::vec2 position);
	GameObject* GetHandObject();

protected:
	int m_itemId;
	int m_count;
	int m_hp;
	//bool m_inInventory;
	bool m_handed;

	Image*			m_image;
	RigidBody2D*	m_rigidbody;
	BoxCollider*	m_collider;
	ColorAnimation* m_pHittedAni;

	//GameObject*		m_handObject;
	//Image*			m_handImage;
private:
	float m_noGetTime;
};

