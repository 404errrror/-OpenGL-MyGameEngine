#include "M_Player.h"
#include "Item.h"
#include "LimitTrap.h"
#include "GameOver.h"

M_Player* M_Player::instance;

M_Player::M_Player()
{
	if (instance == nullptr)
		instance = this;
	else
		m_remove = true;

	SetName("Player");
	m_pImage = nullptr;
	m_pRigid = nullptr;
	m_pColl = nullptr;
	m_pHandItem = nullptr;

	m_attack = m_range = 1.0f;
	m_speed = 1.4f;
	m_isDie = false;
	m_isGameOverPlay = false;
	m_isJump = false;
}


M_Player::~M_Player()
{
}


void M_Player::Initialize()
{
	GameObject::Initialize();
	m_pImage = transform.AddComponent<Image>();
	m_pColl = transform.AddComponent<BoxCollider>();
	m_pRigid = transform.AddComponent<RigidBody2D>();
	m_pColorAni = transform.AddComponent<ColorAnimation>();
	m_pShapeAni = transform.AddComponent<ShapeAnimation>();
	m_pHand = new GameObject();
	m_pDefaultGun = new DefaultGun();
	

	m_pRigid->FreezeRotation(true);
	m_pImage->SetSprite("Miner_Player2");
	m_pHand->SetName("Player_Hand");
	//m_inventory = new Inventory(); 
	//m_pImage->SetSprite("100*100");
	m_pHandItem = m_pDefaultGun;
	GetPhysicsBody()->SetSleepingAllowed(false);
	m_pColorAni->SetColorAnimation(glm::vec4(1.0f, 1.0f, 1.0f, 0.0f), 0.3f, false);
	m_pShapeAni->SetScaleAnimation(glm::vec3(5.0f,5.0f,1.0f), 0.3f, false);
}


void M_Player::Start()
{
	GameObject::Start();
	transform.SetScale(glm::vec3(1.0f));
	transform.SetPositionZ(LAYER_CHARATER);
	m_pColl->SetWidth(m_pImage->GetCoordWidth() * 0.8f);
	m_pColl->SetHeight(m_pImage->GetCoordHeight() * 0.8f);
	m_pRigid->SetGravity(true);

	m_pHand->transform.SetParent(transform);
	m_pHand->transform.SetLocalPosition(glm::vec3(0.0f));
	m_pHand->transform.SetLocalPosition(-0.4f, -0.1f);

	m_pDefaultGun->Attacth(m_pHand->transform);
	m_pHandItem = m_pDefaultGun;
	m_range = m_attack = m_speed = 1.0f;
	m_isDie = false;
	m_isGameOverPlay = false;


}


void M_Player::Update()
{
	GameObject::Update();
	if(m_isDie == false)
	{
		Move();
		//QuitSlot();

		if (m_pHandItem != nullptr)
			m_pHandItem->HandUpdate();

		if (transform.GetPosition().y > LimitTrap::instance->transform.GetPosition().y )
			Die();
	}
	else
	{
		if (m_pColorAni->IsPlay() == false && m_isGameOverPlay == false)
		{
			m_isGameOverPlay = true;
			GameOver::instance->Play();
		}
	}

	if (m_isJump)
		JumpCheck();
}


void M_Player::Release()
{
	GameObject::Release();
	if(instance == this)
		instance = nullptr;
}


void M_Player::SendEvent(std::string message, float value)
{
	if (message == "Die")
		Die();
	else if (message == "RangeIncrease")
		RangeIncrease(value);
	else if (message == "AttackIncrease")
		AttackIncrease(value);
	else if (message == "SpeedIncrease")
		SpeedIncrease(value);
}


void M_Player::Move()
{
	glm::vec3 position = transform.GetPosition();
	float distance = m_pImage->GetCoordWidth() * 0.5f;		// ³Ë³ËÇÏ°Ô.
	float distanceY = m_pImage->GetCoordHeight() * 0.3f;	// ¿ÀÂ÷¶§¹®¿¡ ¾ÆÀÌÅÛ ¸ø¸Ô´Â °æ¿ì°¡ »ý°Ü¼­.
	if (InputManager::IsKeyDown(GLFW_KEY_A))
	{
		//transform.Translate(glm::vec3(-Time::GetDeltaTime() * 2 * m_speed, 0, 0), true);
		RayCastHit* hit = Physics2D::Raycast(
			glm::vec2(position.x, position.y), 
			glm::vec2(position.x - distance, position.y)
		);
		RayCastHit* hitTop = Physics2D::Raycast(
			glm::vec2(position.x, position.y + distanceY),
			glm::vec2(position.x - distance, position.y + distanceY)
		);
		RayCastHit* hitBottom = Physics2D::Raycast(
			glm::vec2(position.x, position.y - distanceY), 
			glm::vec2(position.x - distance, position.y - distanceY)
		);
		if (
			(hit->hitObject			== nullptr || hit->hitObject->GetTag()			== "Item") && 
			(hitTop->hitObject		== nullptr || hitTop->hitObject->GetTag()		== "Item") &&
			(hitBottom->hitObject	== nullptr || hitBottom->hitObject->GetTag()	 == "Item")
			)
			m_pRigid->SetVelocity(glm::vec2(-2 * m_speed, m_pRigid->GetVelocity().y));
		delete hit;
		delete hitTop;
		delete hitBottom;
	}
	if (InputManager::IsKeyDown(GLFW_KEY_D))
	{
		//transform.Translate(glm::vec3(Time::GetDeltaTime() * 2 * m_speed, 0, 0), true);
		RayCastHit* hit = Physics2D::Raycast(
			glm::vec2(position.x, position.y), 
			glm::vec2(position.x + distance, position.y)
		);
		RayCastHit* hitTop = Physics2D::Raycast(
			glm::vec2(position.x, position.y + distanceY), 
			glm::vec2(position.x + distance, position.y + distanceY)
		);
		RayCastHit* hitBottom = Physics2D::Raycast(
			glm::vec2(position.x, position.y - distanceY), 
			glm::vec2(position.x + distance, position.y - distanceY)
		);

		if (
			(hit->hitObject == nullptr || hit->hitObject->GetTag() == "Item") &&
			(hitTop->hitObject == nullptr || hitTop->hitObject->GetTag() == "Item") &&
			(hitBottom->hitObject == nullptr || hitBottom->hitObject->GetTag() == "Item")
			)
			m_pRigid->SetVelocity(glm::vec2(2 * m_speed, m_pRigid->GetVelocity().y));
		delete hit;
		delete hitTop;
		delete hitBottom;
	}


	if (InputManager::IsKeyDownOnce(GLFW_KEY_SPACE) && m_isJump == false)
	{
		distance = m_pImage->GetCoordWidth() * 0.4f;
		distanceY = m_pImage->GetCoordHeight() * 0.5f; // ³Ë³ËÇÏ°Ô.
		//transform.Translate(glm::vec3(-Time::GetDeltaTime() * 2 * m_speed, 0, 0), true);
		RayCastHit* hit = Physics2D::Raycast(
			glm::vec2(position.x, position.y),
			glm::vec2(position.x, position.y - distanceY)
		);
		RayCastHit* hitLeft = Physics2D::Raycast(
			glm::vec2(position.x - distance, position.y),
			glm::vec2(position.x - distance, position.y - distanceY)
		);
		RayCastHit* hitRight = Physics2D::Raycast(
			glm::vec2(position.x + distance, position.y),
			glm::vec2(position.x + distance, position.y - distanceY)
		);
		if (
			(hit->hitObject != nullptr) ||
			(hitLeft->hitObject != nullptr) ||
			(hitRight->hitObject != nullptr)
			)
		{
			m_pRigid->SetVelocity(glm::vec2(0, 7));
		}
		else
		{
			m_pRigid->SetVelocity(glm::vec2(0, 7));
			m_isJump = true;
		}
		delete hit;
		delete hitLeft;
		delete hitRight;

	}
}


void M_Player::JumpCheck()
{
	glm::vec3 position = transform.GetPosition();
	float distance = m_pImage->GetCoordWidth() * 0.4f;		// ³Ë³ËÇÏ°Ô.
	float distanceY = m_pImage->GetCoordHeight() * 0.5f;	// ³Ë³ËÇÏ°Ô.
												   //transform.Translate(glm::vec3(-Time::GetDeltaTime() * 2 * m_speed, 0, 0), true);
	RayCastHit* hit = Physics2D::Raycast(
		glm::vec2(position.x, position.y),
		glm::vec2(position.x, position.y - distanceY)
	);
	RayCastHit* hitLeft = Physics2D::Raycast(
		glm::vec2(position.x - distance, position.y),
		glm::vec2(position.x - distance, position.y - distanceY)
	);
	RayCastHit* hitRight = Physics2D::Raycast(
		glm::vec2(position.x + distance, position.y),
		glm::vec2(position.x + distance, position.y - distanceY)
	);
	if (
		(hit->hitObject != nullptr) ||
		(hitLeft->hitObject != nullptr) ||
		(hitRight->hitObject != nullptr)
		)
		m_isJump = false;
}


//void M_Player::QuitSlot()
//{
//	if (InputManager::IsKeyDownOnce(GLFW_KEY_1))
//	{
//		if (m_pHandItem != nullptr)
//			m_pHandItem->Detatch();
//
//		m_pHandItem = Inventory::instance->GetQuitItem(1);
//		if(m_pHandItem != nullptr)
//			m_pHandItem->Attacth(m_pHand->transform);
//	}
//
//	else if (InputManager::IsKeyDownOnce(GLFW_KEY_2))
//	{
//		if (m_pHandItem != nullptr)
//			m_pHandItem->Detatch();
//
//		m_pHandItem = Inventory::instance->GetQuitItem(2);
//		if (m_pHandItem != nullptr)
//			m_pHandItem->Attacth(m_pHand->transform);
//	}
//	else if (InputManager::IsKeyDownOnce(GLFW_KEY_3))
//	{
//		if (m_pHandItem != nullptr)
//			m_pHandItem->Detatch();
//
//		m_pHandItem = Inventory::instance->GetQuitItem(3);
//		if (m_pHandItem != nullptr)
//			m_pHandItem->Attacth(m_pHand->transform);
//	}
//	else if (InputManager::IsKeyDownOnce(GLFW_KEY_4))
//	{
//		if (m_pHandItem != nullptr)
//			m_pHandItem->Detatch();
//
//		m_pHandItem = Inventory::instance->GetQuitItem(4);
//		if (m_pHandItem != nullptr)
//			m_pHandItem->Attacth(m_pHand->transform);
//	}
//	else if (InputManager::IsKeyDownOnce(GLFW_KEY_5))
//	{
//		if (m_pHandItem != nullptr)
//			m_pHandItem->Detatch();
//
//		m_pHandItem = Inventory::instance->GetQuitItem(5);
//		if (m_pHandItem != nullptr)
//			m_pHandItem->Attacth(m_pHand->transform);
//	}
//	else if (InputManager::IsKeyDownOnce(GLFW_KEY_6))
//	{
//		if (m_pHandItem != nullptr)
//			m_pHandItem->Detatch();
//
//		m_pHandItem = Inventory::instance->GetQuitItem(6);
//		if (m_pHandItem != nullptr)
//			m_pHandItem->Attacth(m_pHand->transform);
//	}
//	else if (InputManager::IsKeyDownOnce(GLFW_KEY_7))
//	{
//		if (m_pHandItem != nullptr)
//			m_pHandItem->Detatch();
//
//		m_pHandItem = Inventory::instance->GetQuitItem(7);
//		if (m_pHandItem != nullptr)
//			m_pHandItem->Attacth(m_pHand->transform);
//	}
//	else if (InputManager::IsKeyDownOnce(GLFW_KEY_8))
//	{
//		if (m_pHandItem != nullptr)
//			m_pHandItem->Detatch();
//
//		m_pHandItem = Inventory::instance->GetQuitItem(8);
//		if (m_pHandItem != nullptr)
//			m_pHandItem->Attacth(m_pHand->transform);
//	}
//}


void M_Player::GetItem(Item* pItem)
{
	if (m_pHandItem == m_pDefaultGun)
	{
		m_pHandItem->Detatch();
		m_pHandItem = pItem;
		m_pHandItem->Attacth(m_pHand->transform);
		SoundManager::Play("GunLoad2");
	}
	else
	{
		m_pHandItem->Throw(MouseManager::GetPosition());
		m_pHandItem = pItem;
		m_pHandItem->Attacth(m_pHand->transform);
		SoundManager::Play("GunLoad2");
	}

}


void M_Player::AttachDefaultGun()
{
	m_pHandItem->Detatch();
	m_pHandItem = m_pDefaultGun;
	m_pHandItem->Attacth(m_pHand->transform);
}


void M_Player::RangeIncrease(float persent)
{
	m_range += persent;
}


void M_Player::AttackIncrease(float persent)
{
	m_attack += persent;
}


void M_Player::SpeedIncrease(float persent)
{
	m_speed += persent;
}


float M_Player::GetRange()
{
	return m_range;
}


float M_Player::GetAttack()
{
	return m_attack;
}


float M_Player::GetSpeed()
{
	return m_speed;
}


Gun* M_Player::GetHandGun()
{
	return (Gun*)m_pHandItem;
}


void M_Player::SetSkin(const char* spriteKey)
{
	m_pImage->SetSprite(spriteKey);
}


void M_Player::Die()
{
	if (m_isDie)
		return;
	m_isDie = true;
	//m_remove = true;
	m_pColorAni->Play();
	m_pShapeAni->PlayScaleAnimation();
	m_pHandItem->Detatch();
	m_pRigid->SetGravity(false);
	m_pRigid->m_enable = false;
	m_pColl->m_enable = false;
}