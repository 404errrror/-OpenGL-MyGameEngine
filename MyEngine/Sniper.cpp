#include "Sniper.h"
#include "M_Player.h"
#include "PistolBullet.h"


Sniper::Sniper()
{
	SetName("Sniper");
	m_damage = 7.0f;
	m_distance = 7.0f;
}


Sniper::~Sniper()
{
}

void Sniper::Initialize()
{
	Item::Initialize();

	m_image->SetSprite("Sniper");
	m_itemId = 403;
	m_bulletCount = 5;
	m_image->SetColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
}


void Sniper::LeftPress()
{
	if (m_delay > 0)
		return;
	m_delay = 1.5f / M_Player::instance->GetSpeed();
	--m_bulletCount;

	glm::vec2 position = glm::vec2(transform.GetPosition().x, transform.GetPosition().y);
	glm::vec2 shootPosition = MouseManager::GetPosition() - position;
	shootPosition = glm::normalize(shootPosition);
	shootPosition *= m_distance * M_Player::instance->GetRange();
	shootPosition += position;

	std::list<RayCastHit*> hitInfoList = Physics2D::RaycastPenetrate(position, shootPosition, HittedManager::activeList);
	
	for (std::list<RayCastHit*>::iterator it = hitInfoList.begin(); it != hitInfoList.end();)
	{
		if ((*it)->hitObject != nullptr)
		{
			(*it)->hitObject->SendEvent("Hitted", m_damage * M_Player::instance->GetAttack());
		}
		delete (*it);
		it = hitInfoList.erase(it);
	}


	PistolBullet* temp = new PistolBullet();
	temp->Initialize();
	temp->Shoot(
		position, shootPosition
	);
	SoundManager::Play("SniperShoot");
}