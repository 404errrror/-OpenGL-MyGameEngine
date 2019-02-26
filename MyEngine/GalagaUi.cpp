#include "GalagaUi.h"
#include "Image.h"
#include "Player.h"

GalagaNumber* GalagaUi::score;

GalagaUi::GalagaUi()
{
	m_pScoreImg =		nullptr;
	m_pHighScoreImg =	nullptr;
	m_pStageTxtImg =	nullptr;
	m_pStage =			nullptr;
	m_pReadyTxtImg =	nullptr;
	m_pLifeImg =		nullptr;
	m_pGameOverImg =	nullptr;

}


GalagaUi::~GalagaUi()
{
}


void GalagaUi::Initialize()
{
	GameObject::Initialize();

	score =				new GalagaNumber();
	m_pScoreImg =		new GameObject();
	m_pHighScoreImg =	new GameObject();
	m_pStageTxtImg =	new GameObject();
	m_pStage =			new GalagaNumber();
	m_pReadyTxtImg =	new GameObject();
	m_pLifeImg =		new GameObject();
	m_pGameOverImg =	new GameObject();

	m_pStage->SetName("StageInfo");

	Image* temp;
	temp = m_pScoreImg->transform.AddComponent<Image>();
	temp->SetSprite("Score");
	temp->SetUI(true);

	temp = m_pHighScoreImg->transform.AddComponent<Image>();
	temp->SetSprite("HighScore");
	temp->SetUI(true);

	temp = m_pStageTxtImg->transform.AddComponent<Image>();
	temp->SetSprite("Stage");
	temp->SetUI(true);

	temp = m_pReadyTxtImg->transform.AddComponent<Image>();
	temp->SetSprite("Ready");
	temp->SetUI(true);

	temp = m_pLifeImg->transform.AddComponent<Image>();
	temp->SetSprite("PlayerImg");
	temp->SetUI(true);

	temp = m_pGameOverImg->transform.AddComponent<Image>();
	temp->SetSprite("GameOver");
	temp->SetUI(true);


	*score = 0;
	*m_pStage = 0;
}


void GalagaUi::Start()
{
	GameObject::Start();
	score->transform.GetComponent<Image>()->SetUI(true);
	score->transform.SetPosition(glm::vec3(-0.9f, 0.8f,0.0f));



	m_pScoreImg->transform.SetScale(glm::vec3(0.6f, 0.15f, 1.0f));
	m_pScoreImg->transform.SetPosition(glm::vec3(-0.8f, 0.9f, 0.0f));

	m_pHighScoreImg->transform.SetScale(glm::vec3(0.6f, 0.15f, 1.0f));
	m_pHighScoreImg->transform.SetPosition(glm::vec3(0.0f, 0.9f, 0.0f));

	m_pStageTxtImg->transform.SetScale(glm::vec3(0.3f, 0.15f, 1.0f));
	m_pStageTxtImg->transform.SetPosition(glm::vec3(0.0f));
	//m_pStageTxtImg->m_active = false;

	m_pReadyTxtImg->transform.SetScale(glm::vec3(0.3f, 0.15f, 1.0f));
	m_pReadyTxtImg->transform.SetPosition(glm::vec3(0.0f));
	m_pReadyTxtImg->m_active = false;

	m_pLifeImg->transform.SetScale(glm::vec3(0.15f,0.2f,0.2f));
	m_pLifeImg->m_active = false;	// 수동으로 업데이트 해줄꺼여서.

	m_pGameOverImg->transform.SetScale(glm::vec3(0.6f, 0.15f, 1.0f));
	m_pGameOverImg->transform.SetPosition(glm::vec3(0.0f));
	m_pGameOverImg->m_active = false;

	m_pStage->transform.GetComponent<Image>()->SetUI(true);
	m_pStage->transform.GetComponent<Image>()->SetColor(glm::vec4(0, 1, 1, 1));
	m_pStage->transform.SetPosition(glm::vec3(0.15f, 0.005f, 0.0f));

}


void GalagaUi::Update()
{
	GameObject::Update();
	if (m_isStart == false)
		Start();
	DrawLife();
}


void GalagaUi::Release()
{
	GameObject::Release();

	m_pScoreImg->m_remove = true;
	m_pHighScoreImg->m_remove = true;
	m_pStageTxtImg->m_remove = true;
	m_pStage->m_remove = true;
	m_pReadyTxtImg->m_remove = true;
	m_pLifeImg->m_remove = true;
	m_pGameOverImg->m_remove = true;
}


void GalagaUi::SetVisibleStage(bool isVisible)
{
	if(isVisible)
		++*m_pStage;
	m_pStageTxtImg->m_active = isVisible;
	m_pStage->m_active = isVisible;
}


void GalagaUi::SetVisibleReady(bool isVisible)
{
	m_pReadyTxtImg->m_active = isVisible;
}


void GalagaUi::GameOver()
{
	m_pGameOverImg->m_active = true;
}


void GalagaUi::DrawLife()
{
	for (int i = 0; i < Player::life; ++i)
	{
		m_pLifeImg->transform.SetPosition(glm::vec3(-0.9f + 0.05f * i, -0.9f, 0));
		//m_pLifeImg->transform.SetPosition(glm::vec3(0));
		m_pLifeImg->transform.GetComponent<Image>()->Update();
	}
}