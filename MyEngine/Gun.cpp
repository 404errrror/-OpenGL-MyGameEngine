#include "Gun.h"
#include "PistolBullet.h"
#include "M_Player.h"
#include "LimitTrap.h"

Gun::Gun()
{
	SetName("Gun");
	SetTag("Item");
	m_distance = 5.0f;
	m_delay = 1.0f;
	m_infinityBullet = false;
}


Gun::~Gun()
{
}


void Gun::Initialize()
{
	Item::Initialize();

	m_image->SetSprite("DefaultGun");
	m_itemId = 400;
	transform.SetPosition(glm::vec3(0, 3, LAYER_ITEM));
}


void Gun::Start()
{
	Item::Start();
	m_collider->SetWidth(m_image->GetCoordWidth() * 0.9f);
	m_collider->SetHeight(m_image->GetCoordHeight() * 0.9f);
	
}


void Gun::Update()
{
	Item::Update();
	/*glm::vec3 rotation = m_handObject->transform.GetRotation();
	glm::vec3 localRotation = m_handObject->transform.GetLocalRotation();
	glm::vec3 position = m_handObject->transform.GetPosition();
	glm::vec3 localPosition = m_handObject->transform.GetLocalPosition();
	std::cout << "Gun Rotation : " << rotation.x << "  " << rotation.y << "  " << rotation.z << std::endl;
	std::cout << "Gun LocalRotation : " << localRotation.x << "  " << localRotation.y << "  " << localRotation.z << std::endl;
	std::cout << "Gun Position : " << position.x << "  " << position.y << "  " << position.z << std::endl;
	std::cout << "Gun LocalPosition : " << localPosition.x << "  " << localPosition.y << "  " << localPosition.z << std::endl;
*/
	if (m_delay > 0)
	{
		m_delay -= Time::GetDeltaTime();
	}

	if (m_bulletCount <= 0 && m_infinityBullet == false)
	{
		m_remove = true;
		M_Player::instance->AttachDefaultGun();
	}

	if (LimitTrap::instance->transform.GetPosition().y < transform.GetPosition().y && GetName() != "DefaultGun")
	{
		if (m_handed)
			M_Player::instance->AttachDefaultGun();
		m_remove = true;
	}
}


void Gun::Release()
{

	Item::Release();
}


void Gun::SendEvent(std::string message, float value)
{
	if (message == "Hitted")
	{
		Hitted(value);
	}
	else if (message == "Destory")
	{
		Destroy();
	}
}


void Gun::HandUpdate()
{
	transform.SetRotation(glm::vec3(0.0f));
	transform.LookAt2D(glm::vec3(
		MouseManager::GetPositionX(), 
		MouseManager::GetPositionY(),
		0.0f
	));
	transform.Rotate(glm::vec3(0,0,-90.0f));		// up 기준으로 바라보기때문에.

	if (M_Player::instance->transform.GetPosition().x > MouseManager::GetPositionX())
	{
		transform.Rotate(glm::vec3(0, 0.0f, 180.0f));
		transform.SetScale(glm::vec3(-1, 1, 1));
	}
	else
	{
		transform.SetScale(glm::vec3(1, 1, 1));
	}
}


int Gun::GetBulletCount()
{
	return m_bulletCount;
}
