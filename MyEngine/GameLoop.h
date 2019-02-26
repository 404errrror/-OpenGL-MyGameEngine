#pragma once
#include "Global.h"
#include "CameraC.h"

#define LIMIT_FPS 60
class GameLoop
{
public:
	GameLoop();
	~GameLoop();

	bool Initialize();
	bool Update();
	bool Release();

private:
	CameraC* m_pDefaultCamera;
	float m_accTime;
	float m_lastTime;
	float m_nowTime;

};

