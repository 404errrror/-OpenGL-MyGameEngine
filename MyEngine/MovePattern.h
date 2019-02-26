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
	/// ȸ�� ������ ����ϴ�. ������ ������״µ� ȸ�� ���� ����Ǿ��ٸ� Clear()�� �������־���մϴ�.
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

