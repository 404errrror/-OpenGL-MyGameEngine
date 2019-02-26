#include "ExplosionBlock.h"



ExplosionBlock::ExplosionBlock()
{
	SetName("ExplosionBlock");
	m_pShapeAni = nullptr;
	m_pColorAni = nullptr;
	m_isBreak = false;

	m_pEffect = nullptr;
	m_pEffectImage = nullptr;
	m_pEffectShapeAni = nullptr;
	m_pEffectColorAni = nullptr;

	m_hp = 1.0f;
}


ExplosionBlock::~ExplosionBlock()
{
}


void ExplosionBlock::Initialize()
{
	Block::Initialize();
	m_pShapeAni = transform.AddComponent<ShapeAnimation>();
	m_pColorAni = transform.AddComponent<ColorAnimation>();  // ---------> 같은 컴포넌트가 2개 이상이여서 GetComponent할때 원하는 애가 호출안될듯.
	m_pRigid = transform.AddComponent<RigidBody2D>();

	m_pImage->SetSprite("ExplosionBlock");
	m_pCollider->SetWidth(m_pImage->GetCoordWidth() * 0.9f);		// 터질때 CollisionEnter를 호출하기 위해.
	m_pCollider->SetHeight(m_pImage->GetCoordHeight() * 0.9f);
	m_pShapeAni->SetScaleAnimation(glm::vec3(5.0f, 5.0f, 1.0f), 0.3f, false);
	m_pColorAni->SetColorAnimation(glm::vec4(1.0f, 1.0f, 1.0f, 0.0f), 0.3f, false);
	m_pRigid->SetGravity(false);
	m_pRigid->FreezeRotation(true);


	m_pEffect = new GameObject;
	m_pEffect->Initialize();
	m_pEffectImage = m_pEffect->transform.AddComponent<Image>();
	m_pEffectImage->SetSprite("Point");
	m_pEffectShapeAni = m_pEffect->transform.AddComponent<ShapeAnimation>();
	m_pEffectColorAni = m_pEffect->transform.AddComponent<ColorAnimation>();

	b2MassData mass;
	mass.mass = 10000;
	GetPhysicsBody()->SetMassData(&mass);
}


void ExplosionBlock::Start()
{
	GameObject::Start();
	m_pEffect->Start();
	m_pEffect->transform.SetPosition(transform.GetPosition());
	m_pEffect->transform.SetScale(glm::vec3(0.0f,0.0f,1.0f));
	m_pEffect->transform.SetParent(transform);
	m_pEffectImage->SetColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	m_pEffectShapeAni->SetScaleAnimation(glm::vec3(3.5f, 3.5f, 1.0f), 1.0f, true);
	m_pEffectColorAni->SetColorAnimation(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f), 1.0f, true);
	m_pEffectShapeAni->PlayScaleAnimation();
	m_pEffectColorAni->Play();
}


void ExplosionBlock::Update()
{
	Block::Update();
	if (m_isBreak)
	{
		m_pCollider->SetHeight(m_pImage->GetCoordHeight());
		m_pCollider->SetWidth(m_pImage->GetCoordWidth());
		if (m_pColorAni->IsPlay() == false)
			m_remove = true;
	}
}


void ExplosionBlock::Release()
{
	Block::Release();
	if(m_pEffect != nullptr)
		m_pEffect->m_remove = true;
}


void ExplosionBlock::Destory()
{
	if(m_isBreak == false)
		DestoryEffect();
}


void ExplosionBlock::DestoryEffect()
{

	if (m_pEffect != nullptr)
		m_pEffect->m_remove = true;
	m_pEffect = nullptr;
	m_pShapeAni->PlayScaleAnimation();
	m_pColorAni->Play();
	m_isBreak = true;
	SoundManager::Play("Explosion");

}


void ExplosionBlock::OnCollisionEnter2D(std::list<BoxCollider*>& colliderList)
{
	for (std::list<BoxCollider*>::iterator it = colliderList.begin(); it != colliderList.end(); ++it)
	{
		std::string name = (*it)->gameObject.GetName();
		if (m_isBreak == false)
		{
			if (name == "Player")
				Destory();
		}

		if(name == "Player")
			(*it)->gameObject.SendEvent("Die");
		else
			(*it)->gameObject.SendEvent("Destory");
	}
}