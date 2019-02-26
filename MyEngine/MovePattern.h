#pragma once
#include "Global.h"

struct PatternData
{
	glm::vec3 rotateData;
	float remainTime;
};

class MovePattern
{
public:
	MovePattern();
	~MovePattern();

	void Update();
	bool IsEnd();
	/// </summary>
	/// 회전 정보를 지웁니다. 패턴을 적용시켰는데 회전 값이 변경되었다면 Clear()를 실행해주어야합니다.
	/// <summary>
	void Clear();
	glm::vec3 GetRotateData();
	void AddPattern(glm::vec3 rotateData, float time);

private:
	std::list<PatternData> m_paternList;
	PatternData m_nowPattern;

	glm::vec3 m_lastRotation;
	float m_accTime;
};

