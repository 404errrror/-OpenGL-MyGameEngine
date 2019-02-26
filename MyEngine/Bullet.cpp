#include "Bullet.h"
#include "Image.h"
#include "Player.h"

std::list<Bullet*> Bullet::myList;

Bullet::Bullet()
{
	myList.push_back(this);
}


Bullet::~Bullet()
{
}


void Bullet::Initialize()
{
	GameObject::Initialize();
	transform.AddComponent<Image>()->SetSprite("PlayerBulletImg");
	transform.SetScale(glm::vec3(0.2f));
}


void Bullet::Start()
{
	GameObject::Start();
}


void Bullet::Update()
{
	GameObject::Update();

	transform.Translate(glm::vec3(0, Time::GetDeltaTime(), 0));
	if (transform.GetPosition().y > 1)
		m_remove = true;
}


void Bullet::Release()
{
	GameObject::Release();
	for(std::list<Bullet*>::iterator it = myList.begin(); it != myList.end(); ++it)
		if (*it == this)
		{
			myList.erase(it);
			Player::bulletCount--;
			return;
		}
}