#pragma once
#include "Scene.h"
#include "GalagaUi.h"

class Player;
class Jako;
class Squad_;
class Stage;
class GalagaNumber;
class StarParticle;

class GameScene :
	public Scene
{
public:
	GameScene();
	~GameScene();

	virtual void Initialize();
	virtual void Update();
	virtual void Release();

private:
	GalagaUi* m_pUI;
	Player* m_pPlayer;
	Squad_* m_pTempSquad;
	StarParticle* m_pStars;

	Stage* m_pStage;
	bool m_isStageStart;
	bool m_isPause;
	float m_delayTime;
	float m_startDelay;
};


