#include "TitleScene.h"
#include "SceneManager.h"
#include "Image.h"


TitleScene::TitleScene() : Scene::Scene("TitleScene")
{
	m_pTitle = nullptr;
	m_pParent = nullptr;
	m_pTitleImage = nullptr;
	m_pPlayerImage = nullptr;
	m_pSelected = nullptr;

	m_isChangeScene = false;
}


TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
	m_pParent = new GameObject();

	m_pTitle = new GameObject();
	m_pTitleImage = m_pTitle->transform.AddComponent<Image>();
	m_pTitleImage->SetSprite("Title");
	m_pTitle->transform.SetParent(m_pParent->transform);

	m_pPlayerImage = (new GameObject())->transform.AddComponent<Image>();
	m_pPlayerImage->SetSprite("PlayerTxt");

	m_pSelected = new GameObject();
	m_pSelected->transform.AddComponent<Image>()->SetSprite("PlayerSelected");

	Scene::Initialize();


	m_pTitle->transform.SetScale(glm::vec3(1.0f, 0.5f, 1.0f));
	m_pTitle->transform.SetPosition(glm::vec3(0.0f, 0.3f, 0.0f));
	m_pTitleImage->SetColor(glm::vec4(0, 1, 0, 1));
	m_pPlayerImage->gameObject.transform.SetScale(glm::vec3(0.3f, 0.3f, 1.0f));
	m_pPlayerImage->gameObject.transform.SetPosition(glm::vec3(0.0f, -0.1f, 0.0f));
	m_pPlayerImage->gameObject.transform.SetParent(m_pParent->transform);
	m_pSelected->transform.SetScale(glm::vec3(0.05f, 0.05f, 0.0f));
	m_pSelected->transform.SetPosition(glm::vec3(-0.2f, -0.04f, 0.0f));
	m_pSelected->transform.SetParent(m_pParent->transform);

	m_pParent->transform.SetPosition(glm::vec3(0.0, -1.0f, 0.0f));

	m_isChangeScene = false;
}


void TitleScene::Update()
{
	Scene::Update();

	Input();
	if (m_isChangeScene)
		return;

	TitleEffect();

	if (m_pParent->transform.GetPosition().y < 0.0f)
		m_pParent->transform.Translate(glm::vec3(0, Time::GetDeltaTime(), 0));
	else if (m_pParent->transform.GetPosition().y > 0.0f)
		m_pParent->transform.SetPosition(glm::vec3(0.0f));
}

void TitleScene::Release()
{
	Scene::Release();
}


void TitleScene::Input()
{
	if (InputManager::IsKeyDownOnce(GLFW_KEY_DOWN))
	{
		m_pSelected->transform.SetLocalPosition(glm::vec3(-0.2f, -0.15f, 0.0f));
	}
	else if(InputManager::IsKeyDownOnce(GLFW_KEY_UP))
	{
		m_pSelected->transform.SetLocalPosition(glm::vec3(-0.2f, -0.03f, 0.0f));
	}
	else if (InputManager::IsKeyDownOnce(GLFW_KEY_SPACE))
	{
		SceneManager::LoadScene("GameScene");
		m_isChangeScene = true;
			// 로드하고 업뎃되면 안되는데 업뎃되서.
	}
}


void TitleScene::TitleEffect()
{
	glm::vec4 color = m_pTitleImage->GetColor();
	if (color.r > 0.7f)
	{
		color.r = 0.0f;
		color.b = 0.0f;
	}
	else
		color.b = color.r += Time::GetDeltaTime();
	m_pTitleImage->SetColor(color);

}