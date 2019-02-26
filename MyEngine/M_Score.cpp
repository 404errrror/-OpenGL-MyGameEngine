#include "M_Score.h"
#include "M_Player.h"
#include "CameraC.h"

M_Score* M_Score::instance;

M_Score::M_Score()
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
	m_pScore = nullptr;
}


M_Score::~M_Score()
{
}


void M_Score::Initialize()
{
	GameObject::Initialize();
	m_pScore = new GalagaNumber();
	m_pScore->SetUnit("Meter");
}


void M_Score::Start()
{
	GameObject::Start();
	*m_pScore = 0;
	m_pScore->transform.SetPosition(glm::vec3(0.0f, 0.0f, LAYER_UI));
	m_pScore->transform.SetScale(glm::vec3(2.0f, 2.0f, 1.0f));
	m_pScore->SetColor(glm::vec4(1.0f, 1.0f, 1.0f, 0.7f));
}


void M_Score::Update()
{
	GameObject::Update();
	glm::vec3 camPosition = CameraC::main->gameObject.transform.GetPosition();
	m_pScore->transform.SetPosition(glm::vec3(-camPosition.x -10.0f, -camPosition.y + 5.0f, LAYER_UI));

	*m_pScore = M_Player::instance->transform.GetPosition().y * -1;
	if (m_pScore->GetData() < 0)
		*m_pScore = 0;
}


void M_Score::Release()
{
	GameObject::Release();
	if (instance == this)
		instance = nullptr;
}


int M_Score::GetScore()
{
	return m_pScore->GetData();
}