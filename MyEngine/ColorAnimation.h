#pragma once
#include "Component.h"

class Image;
class ColorAnimation :
	public Component
{
public:
	static std::list<ColorAnimation*> list;
public:
	ColorAnimation(GameObject& gameObject);
	~ColorAnimation();

	virtual void Update() override;
	virtual void Release() override;

	void SetColorAnimation(glm::vec4 endColor, float time, bool isLoop);
	void SetColorAnimation(glm::vec4 startColor, glm::vec4 endColor, float time, bool isLoop);
	void SetDelay(float time);
	void Play();
	bool IsPlay();
private:
	Image* m_pImage;
	glm::vec4 m_color;
	glm::vec4 m_endColor;
	float m_time;
	float m_endTime;
	float m_delay;
	bool m_isLoop;
	bool m_isActive;
};

