#include "ColorAnimation.h"
#include "Image.h"

std::list<ColorAnimation*> ColorAnimation::list;

ColorAnimation::ColorAnimation(GameObject& gameObject): Component(gameObject)
{
	list.push_back(this);
	m_pImage = nullptr;
	m_color = glm::vec4(0.0f);
	m_endColor = glm::vec4(1.0f);
	m_time = 0.0f;
	m_endTime = 0.0f;
	m_delay = 0.0f;
	m_isLoop = true;
	m_isActive = false;
}


ColorAnimation::~ColorAnimation()
{
}

void ColorAnimation::Update()
{
	if (m_pImage == nullptr)
		m_pImage = GetComponent<Image>();
	if (m_isActive)
	{
		if (m_delay > 0.0f)
		{
			m_delay -= Time::GetDeltaTime();
			return;
		}
		m_time += Time::GetDeltaTime();
		if (m_time < m_endTime)
		{
			float persent = m_time / m_endTime;
			m_pImage->SetColor(m_color * (1 - persent) + m_endColor * persent);
		}
		else
		{
			if (m_isLoop)
				m_time = 0.0f;
			else
			{
				m_pImage->SetColor(m_endColor);
				m_isActive = false;
			}
		}
	}
}


void ColorAnimation::Release()
{
	for(std::list<ColorAnimation*>::iterator it = list.begin(); it != list.end(); ++it)
		if (*it == this)
		{
			list.erase(it);
			return;
		}
}


void ColorAnimation::SetColorAnimation(glm::vec4 endColor, float time, bool isLoop)
{
	if (m_pImage == nullptr)
		m_pImage = GetComponent<Image>();

	m_color = m_pImage->GetColor();
	m_endColor = endColor;
	m_endTime = time;
	m_isLoop = isLoop;
}


void ColorAnimation::SetColorAnimation(glm::vec4 startColor, glm::vec4 endColor, float time, bool isLoop)
{
	if (m_pImage == nullptr)
		m_pImage = GetComponent<Image>();

	m_color = startColor;
	m_endColor = endColor;
	m_endTime = time;
	m_isLoop = isLoop;
}


void ColorAnimation::SetDelay(float time)
{
	m_delay = time;
}


void ColorAnimation::Play()
{
	m_time = 0.0f;
	m_isActive = true;
}


bool ColorAnimation::IsPlay()
{
	return m_isActive;
}