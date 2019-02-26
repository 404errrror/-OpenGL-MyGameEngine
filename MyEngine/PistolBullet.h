#pragma once
#include "MBullet.h"
class PistolBullet :
	public MBullet
{
public:
	PistolBullet();
	~PistolBullet();

	void Initialize() override;
	void Update() override;
	void Shoot(glm::vec2 startPoint, glm::vec2 endPoint) override;

private:
	glm::vec4 m_color;
	Line* m_pLine;
};

