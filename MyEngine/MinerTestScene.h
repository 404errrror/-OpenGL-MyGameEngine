#pragma once
#include "Scene.h"
#include "M_Player.h"
#include "Block.h"
#include "Rifle.h"

#define PTM_RATIO 1  //1 미터당 픽셀 수
class MapCreator;
class InvincibilityBlock;
class StartBlock;

class MinerTestScene :
	public Scene
{
public:
	MinerTestScene();
	~MinerTestScene();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;

	void CreateGround();
	void CreateStartBox();
	void CreateSkinBlock();
	static void GameStart();
	static bool IsStart();
private:
	static bool m_gameStart;
	M_Player* m_pPlayer;
	Block* m_pStartBlock;
	MapCreator* m_mapCreator;
	GameObject* m_pCamera;

private:
	void CameraSetting();
};

