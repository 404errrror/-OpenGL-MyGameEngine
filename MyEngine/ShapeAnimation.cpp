#include "ShapeAnimation.h"
#include "GameObject.h"

std::list<ShapeAnimation*> ShapeAnimation::list;

ShapeAnimation::ShapeAnimation(GameObject& gameObject) : Component(gameObject)
{
	list.push_back(this);

	m_scaleEndTime = 0.0f;
	m_scaleEndScale = glm::vec3(0.0f);
	m_scaleIsLoop = true;
	m_scaleActive = false;
}


ShapeAnimation::~ShapeAnimation()
{
}


void ShapeAnimation::Initialize()
{
	Component::Initialize();
}


void ShapeAnimation::Update()
{
	ScaleAnimation();
}


void ShapeAnimation::Release()
{
	for(std::list<ShapeAnimation*>::iterator it = list.begin(); it != list.end(); ++it)
		if ((*it) == this)
		{
			list.erase(it);
			return;
		}
}


void ShapeAnimation::SetScaleAnimation(glm::vec3 endScale, float time, bool isLoop)
{
	m_scaleEndScale = endScale;
	m_scale = gameObject.transform.GetScale();
	m_scaleEndTime = time;
	m_scaleTime = 0.0f;
	m_scaleIsLoop = isLoop;
	m_scaleActive = false;
}


void ShapeAnimation::PlayScaleAnimation()
{
	m_scaleActive = true;
	m_scaleTime = 0.0f;
}


void ShapeAnimation::ScaleAnimation()
{
	if (m_scaleActive == true)
	{
		m_scaleTime += Time::GetDeltaTime();
		if (m_scaleTime < m_scaleEndTime)
		{
			float persent = m_scaleTime / m_scaleEndTime;
			gameObject.transform.SetScale(m_scale * (1 - persent) + m_scaleEndScale * persent);
		}
		else
		{
			if (m_scaleIsLoop)
				m_scaleTime = 0.0f;
			else
			{
				m_scaleActive = false;
				gameObject.transform.SetScale(m_scaleEndScale);
			}
		}
	}
}