#include "RemainBullet.h"
#include "GalagaNumber.h"
#include "M_Player.h"
#include "CameraC.h"


RemainBullet::RemainBullet()
{
}


RemainBullet::~RemainBullet()
{
}


void RemainBullet::Initialize()
{
	GameObject::Initialize();

	m_pNumber = new GalagaNumber();
	m_pIcon = new GameObject();

	m_pIconImage = m_pIcon->transform.AddComponent<Image>();
}


void RemainBullet::Start()
{
	GameObject::Start();

	m_pNumber->transform.SetScale(glm::vec3(2.0f, 2.0f, 1.0f));
	m_pIcon->transform.SetScale(glm::vec3(1.5f, 1.5f, 1.0f));
	m_pIconImage->m_enable = false;
}


void RemainBullet::Update()
{
	GameObject::Update();
	Gun* nowGun = M_Player::instance->GetHandGun();


	glm::vec3 position = -CameraC::main->gameObject.transform.GetPosition();
	position.x += 8.5f;
	position.y -= 5.5f;
	position.z = LAYER_UI;

	if (nowGun->GetName() == "DefaultGun")			// 기본 총이라면 탄창 무한을 출력.
	{
		m_pNumber->m_active = false;
		m_pIcon->transform.SetScale(glm::vec3(2.0f, 2.0f, 1.0f));
		m_pIconImage->SetSprite("Infinite");
		m_pIcon->transform.SetPosition(position);
		m_pIconImage->Update();
		m_pIcon->transform.SetScale(glm::vec3(1.5f, 1.5f, 1.0f));
	}
	else
	{
		m_pNumber->m_active = true;
		*m_pNumber = nowGun->GetBulletCount();
		m_pNumber->transform.SetPosition(position);
	}

	// 총 이미지 출력
	m_pIconImage->SetSprite(nowGun->transform.GetComponent<Image>()->GetSprite());

	position.y -= 1.0f;
	m_pIcon->transform.SetPosition(position);

	m_pIconImage->Update();
}


void RemainBullet::Release()
{
	GameObject::Release();
}