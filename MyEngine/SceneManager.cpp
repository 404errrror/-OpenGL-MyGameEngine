#include "SceneManager.h"


Scene* SceneManager::nowScene;

SceneManager::SceneManager()
{
	nowScene = nullptr;
}


SceneManager::~SceneManager()
{
}


bool SceneManager::LoadScene(std::string sceneName)
{
	for (std::list<Scene*>::iterator it = Scene::list.begin(); it != Scene::list.end(); ++it)
	{
		if ((*it)->GetName() == sceneName)
		{
			if (nowScene != nullptr)
				nowScene->Release();
			nowScene = *it;
			nowScene->Initialize();
			return true;
		}
	}

	printf("SceneManager::LoadScene  %s �� �����ϴ�. sceneName�� Ȯ�����ּ���.\n");
	return false;
}


void SceneManager::Update()
{
	if (nowScene != nullptr)
		nowScene->Update();
}


void SceneManager::Release()
{
	if (nowScene != nullptr)
		nowScene->Release();
}