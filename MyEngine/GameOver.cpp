#include "GameOver.h"
#include "CameraC.h"
#include "GalagaNumber.h"
#include "M_Score.h"
#include "FileManager.h"

GameOver* GameOver::instance;

GameOver::GameOver()
{
	if (instance == nullptr)
		instance = this;
	else
	{
		m_remove = true;
		m_active = true;
	}
	m_isPlay = false;
	m_pBackground = nullptr;
	m_pBackgroundColorAni = nullptr;
	m_pTextObject = nullptr;
	m_pTextObjectImage = nullptr;
	m_pTextObjectColorAni = nullptr;
}


GameOver::~GameOver()
{
}



void GameOver::Initialize()
{
	GameObject::Initialize();

	m_pTextObject = new GameObject();
	m_pScore = new GalagaNumber();
	m_pBestScore = new GalagaNumber();

	m_pBackground = transform.AddComponent<Image>();
	m_pBackgroundColorAni = transform.AddComponent<ColorAnimation>();

	m_pBackground->SetSprite("Point");
	m_pBackground->SetColor(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));

	transform.SetScale(glm::vec3(2000.0f, 2000.0f, 1.0f));


}


void GameOver::Start()
{
	GameObject::Start();

	m_pTextObjectImage = m_pTextObject->transform.AddComponent<Image>();
	m_pTextObjectColorAni = m_pTextObject->transform.AddComponent<ColorAnimation>();
	m_pScoreColorAni = m_pScore->transform.AddComponent<ColorAnimation>();
	m_pBestScoreColorAni = m_pBestScore->transform.AddComponent<ColorAnimation>();

	m_pTextObjectImage->SetSprite("M_GameOver");
	m_pTextObjectImage->SetColor(glm::vec4(1.0f, 1.0f, 1.0f, 0.0f));

	m_pScore->SetColor(glm::vec4(1.0f, 1.0f, 1.0f, 0.0f));
	m_pBestScore->SetColor(glm::vec4(1.0f, 1.0f, 1.0f, 0.0f));

	m_pTextObject->transform.SetPosition(glm::vec3(0, 0, LAYER_CURSOR - 0.09f));
	m_pScore->transform.SetScale(glm::vec3(1.5f, 1.5f, 1.0f));
	m_pBestScore->transform.SetScale(glm::vec3(1.5f, 1.5f, 1.0f));

	m_pBackgroundColorAni->SetColorAnimation(glm::vec4(0.0f, 0.0f, 0.0f, 0.9f), 1.0f, false);
	m_pTextObjectColorAni->SetColorAnimation(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, false);
	m_pScoreColorAni->SetColorAnimation(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 0.5f, false);
	m_pScoreColorAni->SetDelay(1.0f);
	m_pBestScoreColorAni->SetColorAnimation(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 0.5f, false);
	m_pBestScoreColorAni->SetDelay(1.5f);
}


void GameOver::Update()
{
	GameObject::Update();
	if (m_isPlay)
	{
		glm::vec3 position = -CameraC::main->gameObject.transform.GetPosition();
		transform.SetPosition(glm::vec3(0, 0, LAYER_CURSOR - 0.10f));
		m_pTextObject->transform.SetPosition(glm::vec3(position.x, position.y, LAYER_CURSOR - 0.09f));
		m_pScore->transform.SetPosition(glm::vec3(position.x + 0.9f, position.y - 0.8f, LAYER_CURSOR - 0.09f));
		m_pBestScore->transform.SetPosition(glm::vec3(position.x + 0.9f, position.y - 1.9f, LAYER_CURSOR - 0.09f));
	}
}


void GameOver::Release()
{
	GameObject::Release();
	if (instance == this)
		instance = nullptr;
}


void GameOver::Play()
{
	m_isPlay = true;

	glm::vec3 position = -CameraC::main->gameObject.transform.GetPosition();
	transform.SetPosition(glm::vec3(0, 0, LAYER_CURSOR - 0.10f));
	m_pTextObject->transform.SetPosition(glm::vec3(position.x, position.y, LAYER_CURSOR - 0.09f));
	m_pBackgroundColorAni->Play();
	m_pTextObjectColorAni->Play();
	m_pScoreColorAni->Play();
	m_pBestScoreColorAni->Play();

	// 최고기록 설정.
	*m_pScore = M_Score::instance->GetScore();
	*m_pBestScore = FileManager::GetBestScore();
	if (m_pScore->GetData() > m_pBestScore->GetData())
	{
		FileManager::SetBestScore(m_pScore->GetData());
		*m_pBestScore = FileManager::GetBestScore();
	}
}