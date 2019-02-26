#include "Cursor.h"

Cursor* Cursor::instance;

Cursor::Cursor()
{
	if (instance == nullptr)
	{
		instance = this;
	}
	else
	{
		m_remove = true;
	}
	SetName("Cursor");
	m_pImage = nullptr;
}


Cursor::~Cursor()
{
}


void Cursor::Initialize()
{
	GameObject::Initialize();
	m_pImage = transform.AddComponent<Image>();
}


void Cursor::Start()
{
	GameObject::Start();
	transform.SetPositionZ(LAYER_CURSOR);
	transform.SetPosition(MouseManager::GetPosition().x, MouseManager::GetPosition().y);
	transform.SetScale(glm::vec3(2.0f, 2.0f, 1.0f));
}


void Cursor::Update()
{
	GameObject::Update();
	transform.SetPosition(MouseManager::GetPosition().x, MouseManager::GetPosition().y);
}


void Cursor::Release()
{
	GameObject::Release();
	if (instance == this)
		instance = nullptr;
}


void Cursor::SetSprite(const char* spriteKey)
{
	m_pImage->SetSprite(spriteKey);
}


void Cursor::SetSprite(Sprite* sprite)
{
	m_pImage->SetSprite(sprite);
}


void Cursor::SetColor(glm::vec4 color)
{
	m_pImage->SetColor(color);
}