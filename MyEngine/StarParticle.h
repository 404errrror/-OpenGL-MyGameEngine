#pragma once
#include "GameObject.h"
#include "Global.h"
#define STAR_AMOUNT 50
#define GLITTER_TIME 0.5f
class Image;
class StarParticle :
	public GameObject
{
public:
	StarParticle();
	~StarParticle();

	void Initialize() override;
	void Start() override;
	void Update() override;
	void Release() override;

private:
	Image* m_pImage;
	glm::vec3 m_position[STAR_AMOUNT];
	float m_nowAlpha[STAR_AMOUNT];
	float m_alpha[STAR_AMOUNT];
	float m_glitterTime[STAR_AMOUNT];
	float m_remainTime[STAR_AMOUNT];
};

