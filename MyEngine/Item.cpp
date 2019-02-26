#include "Item.h"
#include "Inventory.h"
#include "M_Player.h"


Item::Item()
{
	SetName("Item");
	SetTag("Item");

	m_itemId = 0;
	m_count = 1;
	m_hp = 10.0f;

	m_image = nullptr;
	m_rigidbody = nullptr;
	m_collider = nullptr;
	m_handed = false;
}


Item::~Item()
{
}


void Item::Initialize()
{
	GameObject::Initialize();
	m_image = transform.AddComponent<Image>();
	m_rigidbody = transform.AddComponent<RigidBody2D>();
	m_collider = transform.AddComponent<BoxCollider>();
	m_pHittedAni = transform.AddComponent<ColorAnimation>();
	transform.SetPositionZ(LAYER_ITEM);
	m_rigidbody->FreezeRotation(true);
	//m_rigidbody->SetGravity(false);

	HittedManager::Add(m_collider);
}


void Item::Start()
{
	GameObject::Start();
	m_collider->SetWidth(10.0f);
	m_collider->SetHeight(10.0f);
	m_pHittedAni->SetColorAnimation(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), 0.5f, false);
}


void Item::Update()
{
	GameObject::Update();

	//if (m_inInventory && transform.gameObject.GetPhysicsBody()->IsActive())
	//{
	//	transform.gameObject.GetPhysicsBody()->SetActive(false);
	//}

	if (m_noGetTime > 0)
	{
		m_noGetTime -= Time::GetDeltaTime();
	}

	if (m_handed)
	{
		MouseManager::State leftState = MouseManager::GetLeftState();
		MouseManager::State rightState = MouseManager::GetRightState();

		switch (leftState)
		{
		case MouseManager::Press:
			LeftPress();
			break;
		case MouseManager::Pressing:
			LeftPressing();
			break;
		case MouseManager::Up:
			LeftUp();
			break;
		}

		switch (rightState)
		{
		case MouseManager::Press:
			RightPress();
			break;
		case MouseManager::Pressing:
			RightPressing();
			break;
		case MouseManager::Up:
			RightUp();
			break;
		}
	}
}


void Item::Release()
{
	GameObject::Release();
	HittedManager::Remove(m_collider);
}


void Item::OnCollisionEnter2D(std::list<BoxCollider*>& colliderList)
{
	for(std::list<BoxCollider*>::iterator it = colliderList.begin(); it != colliderList.end(); ++it)
		if ((*it)->gameObject.GetName() == "Player" && m_noGetTime <= 0)
		{
			//if (Inventory::instance->AddItem(this))
			//{
			//	m_inInventory = true;
			//	m_rigidbody->m_enable = false;
			//}
			M_Player::instance->GetItem(this);
		}
}


void Item::OnCollisionExit2D(BoxCollider* coll)
{

}


void Item::Hitted(float value)
{
	m_hp -= value;
	m_pHittedAni->Play();
	if (m_hp <= 0)
		Destroy();
}


void Item::Destroy()
{
	m_remove = true;
}



int Item::GetItemId()
{
	return m_itemId;
}


void Item::Attacth(Transform& transform)
{
	this->transform.SetParent(transform);
	this->transform.SetLocalPosition(0.0f, 0.0f);
	m_active = true;
	m_handed = true;
	m_rigidbody->m_enable = false;
	m_collider->m_enable = false;
	GetPhysicsBody()->SetActive(false);
	//this->transform.gameObject.GetPhysicsBody()->SetActive(false);
}


void Item::Detatch()
{
	m_active = false;
	m_handed = false;

}


void Item::Throw(glm::vec2 position)
{
	m_active = true;
	m_handed = false;
	m_rigidbody->m_enable = true;
	m_collider->m_enable = true;
	GetPhysicsBody()->SetActive(true);
	m_noGetTime = 1.0f;
	this->transform.RemoveParent();
	m_collider->m_enable = true;
	//this->transform.gameObject.GetPhysicsBody()->SetActive(true);
	m_rigidbody->m_enable = true;
	m_rigidbody->SetGravity(true);

	glm::vec2 velocity = glm::normalize(glm::vec2( position.x - transform.GetPosition().x, position.y - transform.GetPosition().y));

	m_rigidbody->SetVelocity(velocity * 10.0f);
	transform.Translate(glm::vec3(velocity.x, velocity.y,0));
	transform.SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));

}


GameObject* Item::GetHandObject()
{
	//return m_handObject;
	return nullptr;
}