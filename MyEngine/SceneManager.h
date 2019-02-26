#pragma once
#include "Scene.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	static bool LoadScene(std::string sceneName);
	static void Update();
	static void Release();
private:
	static Scene* nowScene;
};

