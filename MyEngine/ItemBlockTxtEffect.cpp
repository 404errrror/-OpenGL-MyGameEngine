#include "ItemBlockTxtEffect.h"
#include "M_Player.h"


ItemBlockTxtEffect::ItemBlockTxtEffect()
{
	SetName("ItemBlockTxtEffect");

	m_pImage = nullptr;
	m_pColorAni = nullptr;
}


ItemBlockTxtEffect::~ItemBlockTxtEffect()
{
}


void ItemBlockTxtEffect::Initialize()
{
	GameObject::Initialize();
	m_pImage = transform.AddComponent<Image>();
	m_pColorAni = transform.AddComponent<ColorAnimation>();
	transform.SetPosition(M_Player::instance->transform.GetPosition());
	transform.SetPositionZ(LAYER_UI);
}


void ItemBlockTxtEffect::Start()
{
	GameObject::Start();

	m_pColorAni->SetColorAnimation(glm::vec4(1.0f, 1.0f, 1.0f, 0.0f), 1.5f, false);
	m_pColorAni->Play();
}


void ItemBlockTxtEffect::Update()
{
	GameObject::Update();
	if (m_pColorAni->IsPlay() == false)
		m_remove = true;
	else
		transform.Translate(glm::vec3(0.0f, Time::GetDeltaTime() * 0.5f, 0.0f), true);

}


void ItemBlockTxtEffect::SetSprite(const char* spriteKey)
{
	m_pImage->SetSprite(spriteKey);
}