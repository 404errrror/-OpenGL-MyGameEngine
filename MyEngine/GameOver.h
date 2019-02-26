#pragma once
#include "GameObject.h"
class GalagaNumber;
class GameOver :
	public GameObject
{
public:
	static GameOver* instance;
public:
	GameOver();
	~GameOver();

	virtual void Initialize();
	virtual void Start();
	virtual void Update();
	virtual void Release();

	void Play();
private:
	bool m_isPlay;
	Image* m_pBackground;
	ColorAnimation* m_pBackgroundColorAni;

	GameObject* m_pTextObject;
	Image* m_pTextObjectImage;
	ColorAnimation* m_pTextObjectColorAni;

	GalagaNumber* m_pScore;
	ColorAnimation* m_pScoreColorAni;

	GalagaNumber* m_pBestScore;
	ColorAnimation* m_pBestScoreColorAni;
};

