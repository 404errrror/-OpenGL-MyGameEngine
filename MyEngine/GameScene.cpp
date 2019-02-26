#include "GameScene.h"
#include "GameObject.h"
#include "Image.h"

#include "Player.h"
#include "Stage.h"
#include "Squad_.h"
#include "MovePattern.h"
#include "GalagaNumber.h"
#include "Enemy.h"
#include "StarParticle.h"
#include "SceneManager.h";

GameScene::GameScene() : Scene("GameScene")
{
	m_pUI = nullptr;
	m_pPlayer = nullptr;
	m_pTempSquad = nullptr;
	m_isStageStart = false;
	m_isPause = false;
	m_pStars = nullptr;
}


GameScene::~GameScene()
{
}


void GameScene::Initialize()
{
	Enemy::count = 0;

	m_pStage = new Stage();
	m_pStars = new StarParticle();
	m_pUI = new GalagaUi();
	m_pPlayer = new Player();



	Scene::Initialize();
	

	//m_pStage->LoadStage();
	m_pUI->SetVisibleStage(true);
	m_pUI->SetVisibleReady(false);
	m_isStageStart = false;
	m_delayTime = 2;
	m_startDelay = 5;


	SoundManager::Play("StartMusic");

}


void GameScene::Update()
{
	m_pStars->Update();		// ��ġ�߿�. ���� ��ҵ��� �׷����� ���� �׷�����.

	Scene::Update();

	if (m_delayTime <= 0)						// �� �ε�ȭ��? ����
	{
		if (m_isStageStart == false)
		{
			m_isStageStart = true;
			m_pUI->SetVisibleStage(false);
			m_pStage->LoadStage();
		}
	}
	else
	{
		if (m_startDelay >= 0)
		{
			m_startDelay -= Time::GetDeltaTime();
		}
		else
		{
			m_delayTime -= Time::GetDeltaTime();
		}
	}


	if (m_isStageStart)
	{
		if (Enemy::count <= 0)
		{
			m_isStageStart = false;
			m_delayTime = 2;
			m_pUI->SetVisibleStage(true);
			//m_pStage->ReleaseStage();			// Release �ϸ� �ȵ�. ���� ������ ������ �����Ǳ� ������.
		}
	}

	if (Player::instance->m_active == false && m_isPause == false)
	{
		if (Player::life <= 0)
			m_pUI->GameOver();
		else
			m_pUI->SetVisibleReady(true);
		m_isPause = true;

	}

	if (m_isPause && Player::life > 0)
	{
		if (InputManager::IsKeyDown(GLFW_KEY_SPACE))
		{
			Player::instance->Respawn();
			m_pUI->SetVisibleReady(false);
			m_isPause = false;
		}
	}

	if (InputManager::IsKeyDownOnce(GLFW_KEY_R))
	{
		SoundManager::Stop("StartMusic");
		SceneManager::LoadScene("TitleScene");
	}
	else if (InputManager::IsKeyDownOnce(GLFW_KEY_L))
	{
		++Player::life;
	}
	else if (InputManager::IsKeyDownOnce(GLFW_KEY_M))
	{
		Player::instance->InfinityBullet();
	}
	

}


void GameScene::Release()
{
	delete m_pStage;
	Scene::Release();
}