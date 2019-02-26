#pragma once
#include "Component.h"
class ShapeAnimation :
	public Component
{
public:
	static std::list<ShapeAnimation*> list;
public:
	ShapeAnimation(GameObject& gameObject);
	~ShapeAnimation();


	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;

	void SetScaleAnimation(glm::vec3 endScale, float time, bool isLoop);

	void PlayScaleAnimation();
private:
	glm::vec3	m_scaleEndScale;
	glm::vec3	m_scale;
	float		m_scaleEndTime;
	float		m_scaleTime;
	bool		m_scaleIsLoop;
	bool		m_scaleActive;

private:
	void ScaleAnimation();
};

