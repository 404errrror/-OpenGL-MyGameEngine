#include "GameObject.h"

std::list<GameObject*> GameObject::list;

GameObject::GameObject() :transform(*(new Transform(*this)))		// transform을 생성.
{
	list.push_back(this);
	m_remove = false;
	m_isStart = false;
	m_active = true;
	m_pPhysicsBody = nullptr;
	//m_pEnterOtherCollider = nullptr;
	m_isInit = false;
	m_tag = "None";
}


GameObject::~GameObject()
{
}


void GameObject::Initialize()
{
	if (m_isInit == true)
		return;
	m_isInit = true;
	m_remove = false;
	m_isStart = false;
	m_active = true;
	transform.Initialize();
}

void GameObject::Start()
{
	m_isStart = true;
}

void GameObject::Update()
{
	if (m_isStart == false)
		Start();
}

void GameObject::Release()
{
	// GameObject::list 에 erase()시켜주는 작업은 Scene에서 하고 있으므로 여기서 하면 절대 안됨.

	if (m_remove == true)
	{
		if (m_pPhysicsBody != nullptr)
		{
			// fixture 삭제.
			for (b2Fixture* fixture = m_pPhysicsBody->GetFixtureList(); fixture;)
			{
				b2Fixture* fixtureToDestroy = fixture;
				fixture = fixture->GetNext();
				m_pPhysicsBody->DestroyFixture(fixtureToDestroy);
			}

			Physics2D::DestoryBody(m_pPhysicsBody);
			m_pPhysicsBody = nullptr;
		}
		transform.Release();
		delete &transform;

	}

}


void GameObject::OnCollisionEnter2D(std::list<BoxCollider*>& colliderList)
{

}


void GameObject::UpdateCollision()
{
	if (m_pEnterOtherColliderList.size() > 0)
	{
		OnCollisionEnter2D(m_pEnterOtherColliderList);
		m_pEnterOtherColliderList.clear();
	}
}


void GameObject::OnCollisionExit2D(BoxCollider* collider)
{

}


void GameObject::SetCollisionEnter(BoxCollider* pCollider)
{
	m_pEnterOtherColliderList.push_back(pCollider);
}


void GameObject::SendEvent(std::string message, float value)
{

}


void GameObject::SetName(const char* name)
{
	m_name = name;
}


void GameObject::SetTag(const char* tag)
{
	m_tag = tag;
}


b2Body* GameObject::SetPhysicsBody(b2Body* body)
{
	body->SetUserData(this);
	return m_pPhysicsBody = body;
}


std::string GameObject::GetName()
{
	return m_name;
}


const char* GameObject::GetTag()
{
	return m_tag;
}


b2Body* GameObject::GetPhysicsBody()
{
	return m_pPhysicsBody;
}