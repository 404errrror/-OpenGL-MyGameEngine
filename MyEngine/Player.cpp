#include "Player.h"
#include "Image.h"
#include "Bullet.h"
#include "RigidBody2D.h"
#include "BoxCollider.h"
#include "Animation.h"

Player* Player::instance = nullptr;
int Player::life;
int Player::bulletCount;

Player::Player()
{
	m_isDie = false;
	m_ignoreAttack = false;
	m_dieCoolTime = 0;
	m_bulletLimit = 2;
	instance = this;
	SetName("Player");
	m_pRigid = nullptr;

	life = 2;
}


Player::~Player()
{
}


void Player::Initialize()
{
					transform.AddComponent<Image>()->SetSprite("PlayerImg");
	m_pAnimation =	transform.AddComponent<Animation>();
	m_pRigid =		transform.AddComponent<RigidBody2D>();
					transform.AddComponent<BoxCollider>();

	transform.SetScale(glm::vec3(0.2f));
	transform.SetPosition(glm::vec3(0, -0.8f, 0));

	m_pAnimation->AddClip("Die");
	m_pAnimation->SetFrame("Die", "PalyerDie_0");
	m_pAnimation->SetFrame("Die", "PalyerDie_1");
	m_pAnimation->SetFrame("Die", "PalyerDie_2");
	m_pAnimation->SetFrame("Die", "PalyerDie_3");
	m_pAnimation->SetFrameDelay(0.15f);
}


void Player::Start()
{
	GameObject::Start();

	BoxCollider& temp = *transform.GetComponent<BoxCollider>();

	temp.SetWidth(transform.GetScale().x - 0.11f);
	temp.SetHeight(transform.GetScale().y - 0.11f);

	transform.GetComponent<RigidBody2D>()->SetCollider(&temp);
}


void Player::Update()
{
	if (m_isStart == false)
		Start();

	if (m_pRigid->GetOtherCollider() != nullptr && m_isDie == false)
		Die();
	if (m_isDie && m_pAnimation->IsPlay() == false)
	{
		m_active = false;
		transform.SetPosition(glm::vec3(0, -0.8f, 0));

	}

	if(m_isDie == false)
		Move();
	if (m_dieCoolTime > 0)
	{
		m_dieCoolTime -= Time::GetDeltaTime();
		if(m_dieCoolTime <= 0)
			transform.GetComponent<Image>()->SetColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	}
}


void Player::Release()
{
	GameObject::Release();
}


void Player::Move()
{
	if (InputManager::IsKeyDown(GLFW_KEY_UP))
		transform.Translate(glm::vec3(0, Time::GetDeltaTime() * 0.5f, 0));
	if (InputManager::IsKeyDown(GLFW_KEY_DOWN))
		transform.Translate(glm::vec3(0, -Time::GetDeltaTime() * 0.5f, 0));
	if (InputManager::IsKeyDown(GLFW_KEY_RIGHT))
		transform.Translate(glm::vec3(Time::GetDeltaTime() * 0.5f, 0, 0));
	if (InputManager::IsKeyDown(GLFW_KEY_LEFT))
		transform.Translate(glm::vec3(-Time::GetDeltaTime() * 0.5f, 0, 0));
	if (InputManager::IsKeyDown(GLFW_KEY_Z))
		transform.Rotate(glm::vec3(0, 0, -Time::GetDeltaTime() * 100.0f));
	if (InputManager::IsKeyDown(GLFW_KEY_X))
		transform.Rotate(glm::vec3(0, 0, Time::GetDeltaTime() * 100.0f));
	if (InputManager::IsKeyDownOnce(GLFW_KEY_SPACE))
	{
		if (m_ignoreAttack == false)		// 왠진 모르겠지만 리스폰할때 스페이스 누른게 없어지지 않고 전달되는듯함.
			Attack();
		else
			m_ignoreAttack = false;
	}
}


void Player::Attack()
{
	if (bulletCount < m_bulletLimit)
	{
		bulletCount++;
		Bullet* tempBullet = new Bullet();
		glm::vec3 bulletPosition = transform.GetPosition();
		bulletPosition.z = 0;

		tempBullet->Initialize();
		tempBullet->transform.SetPosition(bulletPosition);
		tempBullet->transform.SetRotation(transform.GetRotation());

		SoundManager::Play("Shot");
		printf("Shoot!! \n");
	}
}


void Player::Die()
{
	if (m_dieCoolTime <= 0)
	{
		m_isDie = true;
		m_pAnimation->SetClip("Die");
		m_pAnimation->SetLoop(false);
		m_pAnimation->Play();
		SoundManager::Play("PlayerDie");
	}

}


void Player::Respawn()
{
	--life;
	m_isDie = false;
	m_active = true;
	transform.SetPosition(glm::vec3(0, -0.8f, 0));
	transform.GetComponent<Image>()->SetSprite("PlayerImg");
	m_dieCoolTime = 3.0f;
	m_ignoreAttack = true;
	transform.GetComponent<Image>()->SetColor(glm::vec4(1.0f, 1.0f, 1.0f, 0.5f));
}


void Player::InfinityBullet()
{
	m_bulletLimit = 99999;
}