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

	printf("SceneManager::LoadScene  %s 가 없습니다. sceneName을 확인해주세요.\n");
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