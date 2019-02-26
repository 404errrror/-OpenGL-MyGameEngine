#include "EndPattern.h"



EndPattern::EndPattern()
{
	m_isArrive = false;
}


EndPattern::~EndPattern()
{
}


void EndPattern::Update()
{
	if(m_isArrive)
		m_waitSenconds -= Time::GetDeltaTime();


}


void EndPattern::SetEndPosition(glm::vec3 position)
{
	m_endPosition = position;
}


void EndPattern::Arrive(bool isArrive)
{
	m_isArrive = true;
}


bool EndPattern::IsArrive()
{
	return  m_isArrive;
}


glm::vec3 EndPattern::GetEndPosition()
{
	return m_endPosition;
}