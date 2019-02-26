#include "Time.h"

float	Time::m_deltaTime;
int		Time::m_tick;
int		Time::m_lastTick;

float Time::m_time;
float Time::m_lastTime;


Time::Time()
{
}


Time::~Time()
{
}


float Time::GetDeltaTime()
{
	return m_deltaTime;
}


void Time::StartTime()
{
	m_tick = GetTickCount();
	m_time = glfwGetTime();
}


void Time::UpdateTime()
{
	m_lastTick = m_tick;
	m_tick = GetTickCount();
	m_deltaTime = (m_tick - m_lastTick) / 1000.0f;

	m_lastTime = m_time;
	m_time = glfwGetTime();
	m_deltaTime = m_time - m_lastTime;
}