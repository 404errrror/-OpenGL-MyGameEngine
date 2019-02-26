#pragma once
#include "GameObject.h"
#include "Global.h"
#include "GalagaNumber.h"

class GalagaNumber;
class GalagaUi :
	public GameObject
{
public:
	static GalagaNumber* score;

public:
	GalagaUi();
	~GalagaUi();

	void Initialize()	override;
	void Start()		override;
	void Update()		override;
	void Release()		override;

	void SetVisibleStage(bool isVisible);
	void SetVisibleReady(bool isVisible);
	void GameOver();

private:
	GameObject* m_pScoreImg;
	GameObject* m_pHighScoreImg;

	GameObject* m_pStageTxtImg;
	GalagaNumber* m_pStage;

	GameObject* m_pReadyTxtImg;
	GameObject* m_pLifeImg;

	GameObject* m_pGameOverImg;
private:
	void DrawLife();
};

