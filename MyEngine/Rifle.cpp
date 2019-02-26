#include "Rifle.h"
#include "PistolBullet.h"
#include "M_Player.h"

Rifle::Rifle()
{
	m_delay = 0.1f;
	m_damage = 1.8f;
}


Rifle::~Rifle()
{
}



void Rifle::Initialize()
{
	Item::Initialize();

	m_image->SetSprite("Rifle");
	m_itemId = 402;
	m_bulletCount = 50;
	m_image->SetColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
}


void Rifle::LeftPressing()
{
	if (m_delay > 0)
		return;
	m_delay = 0.1f / M_Player::instance->GetSpeed();
	--m_bulletCount;

	glm::vec2 position = glm::vec2(transform.GetPosition().x, transform.GetPosition().y);
	glm::vec2 shootPosition = MouseManager::GetPosition() - position;
	shootPosition = glm::normalize(shootPosition);
	shootPosition *= m_distance * M_Player::instance->GetRange();
	shootPosition += position;

	RayCastHit* hitInfo = Physics2D::Raycast(position, shootPosition, HittedManager::activeList);
	glm::vec2 endPosition = hitInfo->endPoint;

	PistolBullet* temp = new PistolBullet();
	temp->Initialize();
	temp->Shoot(
		position, endPosition
	);

	if (hitInfo->hitObject != nullptr)
	{
		hitInfo->hitObject->SendEvent("Hitted", m_damage * M_Player::instance->GetAttack());
	}
	delete hitInfo;

	SoundManager::Play("DefaultGunShoot");

}