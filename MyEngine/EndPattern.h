#pragma once
#include "Global.h"
class EndPattern
{
public:
	EndPattern();
	~EndPattern();

	void Update();

	void SetEndPosition(glm::vec3 position);
	void Arrive(bool isArrive);
	bool IsArrive();

	glm::vec3 GetEndPosition();
private:
	glm::vec3 m_endPosition;
	float m_waitSenconds;
	bool m_isArrive;
};

