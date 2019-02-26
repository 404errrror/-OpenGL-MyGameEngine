#include "MinerTestScene.h"
#include "Inventory.h"
#include "Cursor.h"
#include "MapCreator.h"
#include "LimitTrap.h"
#include "M_Score.h"
#include "RemainBullet.h"
#include "GameOver.h"
#include "InvincibilityBlock.h"
#include "StartBlock.h"
#include "SceneManager.h"
#include "HittedManager.h"
#include "FileManager.h"
#include "CameraTarget.h"
#include "SkinBlock.h"

//test

bool MinerTestScene::m_gameStart;

MinerTestScene::MinerTestScene() : Scene("MinerTestScene")
{
	m_gameStart = false;
	m_pPlayer = nullptr;
	m_pStartBlock = nullptr;
	m_mapCreator = nullptr;
}


MinerTestScene::~MinerTestScene()
{
}


void MinerTestScene::Initialize()
{


	//new Inventory();
	FileManager::Initialize();
	new Cursor();
	new M_Score();
	new RemainBullet();
	new GameOver();
	new CameraTarget();
	m_pCamera = new GameObject();
	m_pPlayer = new M_Player();
	m_pStartBlock = new StartBlock();

	m_mapCreator = new MapCreator();
	new LimitTrap();


	Scene::Initialize();
	CameraSetting();
	CreateStartBox();
	CreateSkinBlock();

	Cursor::instance->SetSprite("Cursor");
	Cursor::instance->SetColor(glm::vec4(1.0f));
	m_pStartBlock->transform.SetPosition(glm::vec3(0.0f, 5.0f, LAYER_BLOCK));
	m_gameStart = false;

	SoundManager::Play("BreakAdventureBgm");
}


void MinerTestScene::Update()
{
	glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//m_pCursor->transform.SetPosition(MouseManager::GetPosition().x, MouseManager::GetPosition().y);
	//m_pPlayer->transform.SetPosition(
	//	glm::vec3(
	//		position.x, 
	//		position.y,
	//		0.0f));
	Scene::Update();
	//Physics2D::Update();
	HittedManager::Update();

	if (InputManager::IsKeyDownOnce(GLFW_KEY_R))
	{
		SceneManager::LoadScene("MinerTestScene");
	}

}


void MinerTestScene::Release()
{
	Scene::Release();
	HittedManager::Release();
	SoundManager::Stop("BreakAdventureBgm");
	//m_pPhysicsWorld->DestroyBody(m_pTestBody);		// Error
}


void MinerTestScene::CreateGround()
{
	// 1. BodyDef로 좌표 등을 설정
	b2BodyDef groundDef;
	groundDef.position.Set(0, -4.0f);

	// 2. BodyDef로 Body 생성
	b2Body *groundBody = Physics2D::CreateBody(groundDef);

	// 3. FixtureDef로 Shape 생성, 특성 설정

	b2PolygonShape groundBox;
	// 가로 : 10, 세로 2인 박스를 만든다.
	groundBox.SetAsBox(5.0f, 1.0f);

	//b2EdgeShape shape;
	//b2FixtureDef boxShapeDef;
	//boxShapeDef.shape = &shape;

	// 4. Body에 Fixture 등록
	//
	//// 아래쪽
	//shape.Set(b2Vec2(0, 0), b2Vec2(100, 0));
	//groundBody->CreateFixture(&boxShapeDef);

	//// 왼쪽
	//shape.Set(b2Vec2(0, 0), b2Vec2(0, 100));
	//groundBody->CreateFixture(&boxShapeDef);

	//// 위쪽
	//shape.Set(b2Vec2(0, 100), b2Vec2(100, 100));
	//groundBody->CreateFixture(&boxShapeDef);

	//// 오른쪽
	//shape.Set(b2Vec2(100, 100), b2Vec2(100, 0));

	groundBody->CreateFixture(&groundBox,0.0f);
}


void MinerTestScene::CreateStartBox()
{
	for (int y = -1; y <= 7; y++)
	{
		for (int x = -10; x <= 10; x++)
		{
			if (y == 7 || y == -1 || x == -10 || x == 10)
			{
				InvincibilityBlock* temp = new InvincibilityBlock();
				temp->Initialize();
				temp->transform.SetPosition(glm::vec3(x, y, LAYER_BLOCK));
			}
		}
	}
}


void MinerTestScene::CreateSkinBlock()
{
	SkinBlock* pSkinBlock = new SkinBlock();
	pSkinBlock->Initialize();
	pSkinBlock->SetSkin("Miner_Player2");
	pSkinBlock->transform.SetPosition(glm::vec3(-3, 5, LAYER_BLOCK));

	pSkinBlock = new SkinBlock();
	pSkinBlock->Initialize();
	pSkinBlock->SetSkin("HeroesSkin");
	pSkinBlock->transform.SetPosition(glm::vec3(-5, 5, LAYER_BLOCK));

	pSkinBlock = new SkinBlock();
	pSkinBlock->Initialize();
	pSkinBlock->SetSkin("CatSkin");
	pSkinBlock->transform.SetPosition(glm::vec3(3, 5, LAYER_BLOCK));

	pSkinBlock = new SkinBlock();
	pSkinBlock->Initialize();
	pSkinBlock->SetSkin("CharacterSkin");
	pSkinBlock->transform.SetPosition(glm::vec3(5, 5, LAYER_BLOCK));

	pSkinBlock = new SkinBlock();
	pSkinBlock->Initialize();
	pSkinBlock->SetSkin("MeatBoySkin");
	pSkinBlock->transform.SetPosition(glm::vec3(7, 5, LAYER_BLOCK));
}


void MinerTestScene::GameStart()
{
	m_gameStart = true;

	for (std::list<Block*>::iterator it = InvincibilityBlock::list.begin(); it != InvincibilityBlock::list.end(); ++it)
	{
		(*it)->Destory();
	}
	InvincibilityBlock::list.clear();
}


bool MinerTestScene::IsStart()
{
	return m_gameStart;
}


void MinerTestScene::CameraSetting()
{
	m_pCamera->transform.AddComponent<CameraC>();
	m_pCamera->transform.AddComponent<Follow>();
	//m_pCamera->transform.SetPosition(glm::vec3(0, 0.0f, 0.0f));
	//m_pCamera->transform.LookAt(glm::vec3(0, 0, 0));
	m_pCamera->transform.GetComponent<Follow>()->SetTarget(&CameraTarget::instance->transform);
	//CameraC::main->SetViewType(CameraC::ViewType::Perspective);
	CameraC::main->SetViewType(CameraC::ViewType::Ortho);
}