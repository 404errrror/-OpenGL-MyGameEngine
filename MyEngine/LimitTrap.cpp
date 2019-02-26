#include "LimitTrap.h"
#include "CameraC.h"
#include "MinerTestScene.h"
#include "GalagaNumber.h"
LimitTrap* LimitTrap::instance;

LimitTrap::LimitTrap()
{
	if (instance == nullptr)
	{
		instance = this;
	}
	else
	{
		m_remove = true;
		m_active = false;
	}
	m_speed = 0.7f;
}


LimitTrap::~LimitTrap()
{
}


void LimitTrap::Initialize()
{
	GameObject::Initialize();
	m_pImage = transform.AddComponent<Image>();
	m_pImage->SetSprite("Point");
	transform.SetPosition(glm::vec3(0.0f, 9.0f, LAYER_BLOCK + 0.01f));

	m_pDistance = new GalagaNumber();
	m_pMarkImage = (new GameObject)->transform.AddComponent<Image>();
	m_pMarkImage->SetSprite("TrapMark");
	m_pMarkImage->m_enable = false;
	m_pDistance->m_active = false;

}


void LimitTrap::Start()
{
	GameObject::Start();
	transform.SetScale(glm::vec3(100.0f, 0.2f, 1.0f));
	transform.SetPosition(glm::vec3(0.0f, 9.0f, LAYER_BLOCK + 0.01f));
	m_pDistance->transform.SetScale(glm::vec3(1.5f, 1.5f, 1.0f));
}


void LimitTrap::Update()
{
	GameObject::Update();

	if (MinerTestScene::IsStart())
	{
		transform.Translate(glm::vec3(0.0f, -m_speed * Time::GetDeltaTime(), 0.0f), true);

		glm::vec2 position = glm::vec2(-CameraC::main->gameObject.transform.GetPosition().x, transform.GetPosition().y);
		transform.SetPosition(position.x, position.y);

		m_speed += Time::GetDeltaTime() * 0.01f;

		TrapMark();
	}

}


void LimitTrap::Release()
{
	GameObject::Release();
	if (instance == this)
		instance = nullptr;
}


void LimitTrap::TrapMark()
{
	*m_pDistance = transform.GetPosition().y - M_Player::instance->transform.GetPosition().y;

	if (m_pDistance->GetData() < 8)
	{
		m_pDistance->m_active = false;
		m_pMarkImage->m_enable = false;
	}
	else
	{
		m_pDistance->m_active = true;
		m_pMarkImage->m_enable = true;
		m_pMarkImage->gameObject.transform.SetPosition(-CameraC::main->gameObject.transform.GetPosition().x, -CameraC::main->gameObject.transform.GetPosition().y + 7.0f);
		m_pDistance->transform.SetPosition(-CameraC::main->gameObject.transform.GetPosition().x+ 0.9f, -CameraC::main->gameObject.transform.GetPosition().y + 7.0f);
	};
}