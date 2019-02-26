#include "Block.h"
#include "M_Player.h"
#include "BlockManager.h"
#include "HittedManager.h"
#include "LimitTrap.h"
#include "Particle.h"


Block::Block()
{
	SetName("DefaultBlock");

	BlockManager::instance->activeList.push_back(this);

	 m_pImage = nullptr;
	 m_pCollider = nullptr;
	 m_pHittedAni = nullptr;
	 m_hp = 10.0f;
}


Block::~Block()
{
}


void Block::Initialize()
{
	GameObject::Initialize();
	m_pImage = transform.AddComponent<Image>();
	m_pCollider = transform.AddComponent<BoxCollider>();
	m_pHittedAni = transform.AddComponent<ColorAnimation>();

	HittedManager::Add(m_pCollider);

	m_pImage->SetSprite("GroundBlock");
	//m_pImage->SetSprite("100*100");



}


void Block::Start()
{
	GameObject::Start();

	transform.SetScale(glm::vec3(1.0f));
	transform.SetPositionZ(LAYER_BLOCK);
	m_pCollider->SetHeight(m_pImage->GetCoordHeight());
	m_pCollider->SetWidth(m_pImage->GetCoordWidth());
	m_pHittedAni->SetColorAnimation(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec4(0.0f,0.0f,0.0f,1.0f), 0.5f, false);
}


void Block::Update()
{
	GameObject::Update();
	float top = transform.GetPosition().y + m_pImage->GetCoordHeight() * 0.5f;
	if (top > LimitTrap::instance->transform.GetPosition().y)
	{
		Destory();
	}
}


void Block::Release()
{
	GameObject::Release();
	HittedManager::Remove(m_pCollider);
	for (std::list<Block*>::iterator it = BlockManager::instance->activeList.begin(); it != BlockManager::instance->activeList.end(); ++it)
	{
		if (*it == this)
		{
			BlockManager::instance->activeList.erase(it);
			return;
		}
	}
	for (std::list<Block*>::iterator it = BlockManager::instance->inactiveList.begin(); it != BlockManager::instance->inactiveList.end(); ++it)
	{
		if (*it == this)
		{
			BlockManager::instance->inactiveList.erase(it);
			return;
		}
	}
}


void Block::SendEvent(std::string message, float value)
{
	if (message == "Hitted")
	{
		Hitted(value);
	}
	else if (message == "Destory")
	{
		Destory();
	}
}


void Block::Hitted(float damage)
{
	m_hp -= damage;
	if (m_hp <= 0.0f)
		Destory();
	m_pHittedAni->Play();
}


void Block::Destory()
{
	m_remove = true;
	DestoryEffect();
}


void Block::DestoryEffect()
{
	// 절대 배열을 사용하면 안됨. Release할 때 delete[] 해야하는데 delete해서 에러가 남.
	for (int i = 0; i < 10; ++i)
	{
		Particle* particleArr = new Particle;
		particleArr->Initialize();
		particleArr->Start();
		particleArr->transform.AddComponent<RigidBody2D>()->SetVelocity(glm::vec2(Random::Range(-10.0f, 10.0f), Random::Range(-10.0f, 10.0f)));
		BoxCollider* coll = particleArr->transform.AddComponent<BoxCollider>();
		coll->SetIgnoreRaycast(true);
		particleArr->transform.SetScale(glm::vec3(0.3f, 0.3f, 1.0f));
		coll->SetHeight(particleArr->transform.GetComponent<Image>()->GetCoordHeight());
		coll->SetWidth(particleArr->transform.GetComponent<Image>()->GetCoordWidth());
		particleArr->transform.SetPosition(transform.GetPosition());
		particleArr->GetImage()->SetColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
		particleArr->SetFade(1.0f);
	}

}