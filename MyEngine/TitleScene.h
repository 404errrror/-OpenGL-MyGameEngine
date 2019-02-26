#pragma once
#include "Scene.h"

class TitleScene :
	public Scene
{
public:
	TitleScene();
	~TitleScene();

	void Initialize() override;
	void Update() override;
	void Release() override;

private:
	void Input();
	void TitleEffect();

private:
	GameObject* m_pTitle;
	GameObject* m_pParent;
	Image* m_pTitleImage;
	Image* m_pPlayerImage;
	GameObject* m_pSelected;

	bool m_isChangeScene;
};

