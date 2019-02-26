#include "MovePattern.h"
#include "Stage.h"


MovePattern::MovePattern()
{
	m_nowPattern.rotateData = glm::vec3(0);
	m_nowPattern.remainTime = 0;
	m_accTime = 0;

}


MovePattern::~MovePattern()
{
}


void MovePattern::Update()
{
	m_accTime += Time::GetDeltaTime();


	if (m_nowPattern.remainTime <= m_accTime)
	{
		if (m_paternList.empty() == false)
		{
			m_lastRotation += m_nowPattern.rotateData;
			m_accTime = 0;
			m_nowPattern = m_paternList.front();
			m_paternList.pop_front();
		}
	}
}


bool MovePattern::IsEnd()
{
	if (m_nowPattern.remainTime <= m_accTime && m_paternList.empty())
		return true;
	else
		return false;
}


void MovePattern::Clear()
{
	m_nowPattern.rotateData = m_lastRotation = glm::vec3(0);
}


glm::vec3 MovePattern::GetRotateData()
{
	if (m_paternList.empty() && m_nowPattern.remainTime <= m_accTime)
	{
		return m_lastRotation + m_nowPattern.rotateData;
	}
	else
	{
		return m_lastRotation + m_nowPattern.rotateData * (m_accTime / m_nowPattern.remainTime);
	}
} 


void MovePattern::AddPattern(glm::vec3 rotateData, float time)
{
	m_paternList.push_back(PatternData{ rotateData, time / (0.7f + ((float)Stage::m_nowStage * 0.3f)) });
	//m_accTime = 0;
}