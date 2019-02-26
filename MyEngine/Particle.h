#pragma once
#include "GameObject.h"
class Particle :
	public GameObject
{
public:
	Particle();
	~Particle();

	virtual void Initialize();
	virtual void Start();
	virtual void Update();
	virtual void Release();

	Image* GetImage();
	void SetFade(float time);

private:
	Image* m_pImage;
	float m_fadeTime;
	float m_fadeBaseAlpha;
	float m_time;
};

