#include "DefaultGun.h"
#include "PistolBullet.h"
#include "M_Player.h"

DefaultGun::DefaultGun()
{
	SetName("DefaultGun");
	m_damage = 5.0f;
}


DefaultGun::~DefaultGun()
{
}


void DefaultGun::Initialize()
{
	Item::Initialize();

	m_image->SetSprite("DefaultGun");
	m_itemId = 401;
	m_infinityBullet = true;
	//m_collider->m_enable = false;
	m_image->SetColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
}


void DefaultGun::LeftPress()
{
	if (m_delay > 0)
		return;
	m_delay = 0.5f / M_Player::instance->GetSpeed();

	glm::vec2 startPoint = glm::vec2(transform.GetPosition().x, transform.GetPosition().y);
	glm::vec2 endPoint;

	// 총알 끝점 계산
	endPoint = MouseManager::GetPosition() - startPoint;
	endPoint = glm::normalize(endPoint);
	endPoint *= m_distance * M_Player::instance->GetRange();
	endPoint += glm::vec2(startPoint.x, startPoint.y);

	RayCastHit* rayInfo = Physics2D::Raycast(startPoint, endPoint, HittedManager::activeList);


	PistolBullet* temp = new PistolBullet();
	temp->Initialize();

	temp->Shoot(
		glm::vec2(startPoint.x, startPoint.y), glm::vec2(rayInfo->endPoint.x, rayInfo->endPoint.y)
	);
	SoundManager::Play("DefaultGunShoot");
	if (rayInfo->hitObject != nullptr)
		rayInfo->hitObject->SendEvent("Hitted", m_damage * M_Player::instance->GetAttack());
	delete rayInfo;
}


void DefaultGun::Release()
{
	Gun::Release();
}