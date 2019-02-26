#include "GameLoop.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "SpriteManager.h"
#include "ShaderManager.h"

//#include "GameScene.h"
//#include "TitleScene.h"
#include "MinerTestScene.h"

GameLoop::GameLoop()
{
	m_pDefaultCamera = nullptr;
	m_nowTime = m_lastTime = m_accTime = 0;
}


GameLoop::~GameLoop()
{
}


bool GameLoop::Initialize()
{

	glfwSetInputMode(g_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	SpriteManager::ImageLoading();
	ShaderManager::ShaderLoading();
	SoundManager::Loading();
	Physics2D::Initialize();
	MouseManager::Initialize();

	// CameraSetting
	//Camera::SetProjection(
	//	glm::radians(70.0f), (float)g_width / (float)g_height,
	//	0.1f,
	//	100.0f
	//);
	//Camera::SetView(
	//	glm::vec3(0, -1.2f, 0.5f),
	//	glm::vec3(0, 0, 0),
	//	glm::vec3(0, 1, 0)
	//);
	//Camera::SetOrthoView(
	//	glm::vec3(0, 0, 0.5f),
	//	glm::vec3(0, 0, 0),
	//	glm::vec3(0, 1, 0)
	//);

	//m_pDefaultCamera = (new GameObject())->transform.AddComponent<CameraC>();
	//m_pDefaultCamera->gameObject.transform.SetPosition(glm::vec3(0, -1.2f, 0.5f));
	////m_pDefaultCamera->gameObject.transform.SetRotation(glm::vec3(0, 0, 180.0f));
	//m_pDefaultCamera->gameObject.transform.LookAt(glm::vec3(0, 0, 0));
	//m_pDefaultCamera->SetViewType(CameraC::ViewType::Perspective);


	//GameScene* gameScene = new GameScene();
	//TitleScene* titleScene = new TitleScene();
	MinerTestScene* minerTestScene = new MinerTestScene();

	SceneManager::LoadScene("MinerTestScene");
	//SceneManager::LoadScene("GameScene");
	//SceneManager::LoadScene("TitleScene");
	Time::StartTime();
	return true;
}


bool GameLoop::Update()
{
	m_nowTime = glfwGetTime();
	if (m_lastTime != 0)
		m_accTime += m_nowTime - m_lastTime;

	if (m_accTime < (1.0f / LIMIT_FPS))
	{
		m_lastTime = m_nowTime;
		return true;
	}

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	Time::UpdateTime();

	m_accTime = 0;
	SceneManager::Update();
	//g_debugDraw.Flush();
	m_lastTime = m_nowTime;

	// Ä«¸Þ¶ó
	//if (InputManager::IsKeyDown(GLFW_KEY_P))
	//	Camera::PerspectiveButton(true);
	//else if(InputManager::IsKeyDown(GLFW_KEY_O))
	//	Camera::PerspectiveButton(false);
	InputManager::KeyUpdate();
	MouseManager::Update();
	glfwSwapBuffers(g_window);
	glfwPollEvents();


	if (glfwGetKey(g_window, GLFW_KEY_ESCAPE) == GLFW_PRESS ||
		glfwWindowShouldClose(g_window) == true)
		return false;
	else
		return true;
}

bool GameLoop::Release()
{
	SceneManager::Release();
	SpriteManager::Release();
	SoundManager::Release();
	return true;
}