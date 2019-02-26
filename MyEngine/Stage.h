#pragma once
#include "Global.h"
#include "EndPattern.h"

#define SQUAD_SIZE 8
class Squad_;
class Stage
{
public:
	Stage();
	~Stage();

	static int m_nowStage;

	void LoadStage();
	//void ReleaseStage();

private:
	Squad_* m_pSquad[SQUAD_SIZE];
	
	template<typename T>
	T* GenerateEnemy(T* enemy, glm::vec3 endPosition);

};


template<typename T>
T* Stage::GenerateEnemy(T* enemy, glm::vec3 endPosition)
{
	EndPattern temp;
	temp.SetEndPosition(endPosition);

	enemy->SetEndPattern(temp);

	return enemy;
}