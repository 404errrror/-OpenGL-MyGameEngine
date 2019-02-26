#pragma once
#include "Global.h"
class Time
{
public:
	Time();
	~Time();

	static float	GetDeltaTime();
	static void		StartTime();
	static void		UpdateTime();

private:
	static float m_deltaTime;
	static int m_tick;
	static int m_lastTick;

	static float m_time;
	static float m_lastTime;
};

