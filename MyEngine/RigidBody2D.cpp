#include "RigidBody2D.h"
#include "GameObject.h"
#include "BoxCollider.h"

std::list<RigidBody2D*> RigidBody2D::list;

RigidBody2D::RigidBody2D(GameObject& gameObject) : Component(gameObject)
{
	list.push_back(this);
	m_pColl = nullptr;
	m_pOtherColl = nullptr;
	velocity = glm::vec3(0.0f);
	m_isTrigger = true;
	m_useGravity = true;
	m_body = nullptr;
}


RigidBody2D::~RigidBody2D()
{
}


void RigidBody2D::Initialize()
{
	Component::Initialize();
	
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;

	bodyDef.position.Set(
		gameObject.transform.GetPosition().x,
		gameObject.transform.GetPosition().y
	);

	m_body = gameObject.GetPhysicsBody();
	if (m_body == nullptr)
		m_body = gameObject.SetPhysicsBody(Physics2D::CreateBody(bodyDef));
	else
	{
		m_body->SetType(b2_dynamicBody);
		m_body->SetTransform(bodyDef.position, 0.0f);
	}
}


void RigidBody2D::Update()
{
	Component::Update();

	if (m_body->IsAwake())
	{
		//b2Vec2 velocity = m_body->GetLinearVelocity() ;
		//gameObject.transform.Translate(glm::vec3(
		//	velocity.x * Physics2D::fixedTime * Physics2D::stepCount, 
		//	velocity.y *  Physics2D::fixedTime * Physics2D::stepCount, 0.0f), true);

		glm::vec3 rotation = gameObject.transform.GetRotation();
		gameObject.transform.SetPosition(glm::vec3(
			m_body->GetPosition().x,
			m_body->GetPosition().y,
			gameObject.transform.GetPosition().z
		));
		gameObject.transform.SetRotation(glm::vec3(
			rotation.x, rotation.y, -m_body->GetAngle() * 180.0f / glm::pi<float>()
		));
	}
	//glm::vec3 position = gameObject.transform.GetPosition();
	//m_body->SetTransform(b2Vec2(position.x, position.y), 0.0f);

}


void RigidBody2D::Release()
{
	Component::Release();
	//m_body->SetActive(false);

	for (std::list<RigidBody2D*>::iterator it = list.begin(); it != list.end(); ++it)
	{
		if (*it == this)
		{
			list.erase(it);
			return;
		}
	}
}


bool RigidBody2D::IsTrigger()
{
	return m_isTrigger;
}


void RigidBody2D::SetTrigger(bool isTrigger)
{
	m_isTrigger = isTrigger;
}


void RigidBody2D::SetCollider(BoxCollider* boxCollider)
{
	m_pColl = boxCollider;
}


void RigidBody2D::SetGravity(bool useGravity)
{
	m_useGravity = useGravity;
	if(m_useGravity == false)
		m_body->SetGravityScale(0.0f);
}


void RigidBody2D::SetVelocity(glm::vec2 velocity)
{
	m_body->SetLinearVelocity(b2Vec2(velocity.x, velocity.y));
}


bool RigidBody2D::IsCollision(glm::vec2 point)
{
	if (m_pColl->CollisionCheck(point))
		return true;
	else return false;
}


bool RigidBody2D::IsCollision(BoxCollider boxColl)
{
	return false;
}


BoxCollider* RigidBody2D::GetOtherCollider()
{
	return m_pOtherColl;
}


glm::vec2 RigidBody2D::GetVelocity()
{
	b2Vec2 velocity = m_body->GetLinearVelocity();
	return glm::vec2(velocity.x,velocity.y);
}


void RigidBody2D::FreezeRotation(bool freeze)
{
	m_body->SetFixedRotation(freeze);
}


void RigidBody2D::CollisionPhysics()
{

	
}


void RigidBody2D::OldCode()
{
	m_pOtherColl = nullptr;

	// 중력
	if (m_useGravity)
	{
		velocity += glm::vec3(0, -9.81f * Time::GetDeltaTime(), 0);
	}

	if (m_pColl != nullptr)
	{
		for (std::list<BoxCollider*>::iterator it = BoxCollider::list.begin(); it != BoxCollider::list.end(); ++it)
		{
			if ((*it) == m_pColl)		// 자기자신 충돌체크 하는 것을 막기위해.
				continue;
			if ((*it)->m_enable == false)
				continue;

			glm::vec2 otherPosition = glm::vec2((*it)->gameObject.transform.GetPosition());
			float halfWidth = (*it)->GetWidth() * 0.5f;
			float halfHeight = (*it)->GetHeight() * 0.5f;

			if (
				m_pColl->CollisionCheck(glm::vec2(otherPosition.x - halfWidth, otherPosition.y + halfHeight)) ||
				m_pColl->CollisionCheck(glm::vec2(otherPosition.x - halfWidth, otherPosition.y - halfHeight)) ||
				m_pColl->CollisionCheck(glm::vec2(otherPosition.x + halfWidth, otherPosition.y - halfHeight)) ||
				m_pColl->CollisionCheck(glm::vec2(otherPosition.x + halfWidth, otherPosition.y + halfHeight))
				)
			{
				m_pOtherColl = (*it);
			}

		}
	}

	if (m_isTrigger == false && m_pOtherColl != nullptr)
	{
		////
		// 물리 처리 코드.
		////


	}

	// veocity 결과 값을 적용
	gameObject.transform.Translate(velocity, true);
}