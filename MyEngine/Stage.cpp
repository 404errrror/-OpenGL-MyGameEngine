#include "Stage.h"
#include "Squad_.h"
#include "MovePattern.h"
#include "Enemy.h"

#include "Jako.h"
#include "Goei.h"
#include "Boss1.h"

int Stage::m_nowStage;

Stage::Stage()
{
	m_nowStage = 0;
	for (int i = 0; i < SQUAD_SIZE; ++i)
		m_pSquad[i] = nullptr;
}


Stage::~Stage()
{
}


void Stage::LoadStage()
{
	++m_nowStage;
	MovePattern pattern;
	//switch (m_nowStage)
	//{
	//case 1:
	//{
		pattern.AddPattern(glm::vec3(0, 0, 180), 0.1f);
		pattern.AddPattern(glm::vec3(0, 0, 45), 1.0f);
		pattern.AddPattern(glm::vec3(0, 0, 0), 0.5f);
		pattern.AddPattern(glm::vec3(0, 0, -240), 0.7f);
		pattern.AddPattern(glm::vec3(0, 0, 40), 0.3f);

		m_pSquad[0] = new Squad_(pattern);
		m_pSquad[0]->AddEnemy(GenerateEnemy(new Jako, glm::vec3(-0.05f, 0.3f, 0)));
		m_pSquad[0]->AddEnemy(GenerateEnemy(new Jako, glm::vec3(0.05f, 0.3f, 0)));
		m_pSquad[0]->AddEnemy(GenerateEnemy(new Jako, glm::vec3(-0.05f, 0.2f, 0)));
		m_pSquad[0]->AddEnemy(GenerateEnemy(new Jako, glm::vec3(0.05f, 0.2f, 0)));
		m_pSquad[0]->SetSpawnPoint(glm::vec3(0.15f, 1.2f, 0));

		pattern = MovePattern();
		pattern.AddPattern(glm::vec3(0, 0, -180), 0.1f);
		pattern.AddPattern(glm::vec3(0, 0, -45), 1.0f);
		pattern.AddPattern(glm::vec3(0, 0, 0), 0.5f);
		pattern.AddPattern(glm::vec3(0, 0, 240), 0.7f);
		pattern.AddPattern(glm::vec3(0, 0, -40), 0.3f);
		m_pSquad[1] = new Squad_(pattern);
		m_pSquad[1]->AddEnemy(GenerateEnemy(new Goei, glm::vec3(-0.05f, 0.5f, 0)));
		m_pSquad[1]->AddEnemy(GenerateEnemy(new Goei, glm::vec3(0.05f, 0.5f, 0)));
		m_pSquad[1]->AddEnemy(GenerateEnemy(new Goei, glm::vec3(-0.05f, 0.4f, 0)));
		m_pSquad[1]->AddEnemy(GenerateEnemy(new Goei, glm::vec3(0.05f, 0.4f, 0)));
		m_pSquad[1]->SetSpawnPoint(glm::vec3(-0.15f, 1.2f, 0));

		pattern = MovePattern();
		pattern.AddPattern(glm::vec3(0, 0, 45), 0.1f);
		pattern.AddPattern(glm::vec3(0, 0, 0), 0.5f);
		pattern.AddPattern(glm::vec3(0, 0, -45), 0.5f);
		pattern.AddPattern(glm::vec3(0, 0, -360), 0.7f);
		pattern.AddPattern(glm::vec3(0, 0, 20), 0.1f);
		m_pSquad[2] = new Squad_(pattern);
		m_pSquad[2]->AddEnemy(GenerateEnemy(new Boss1, glm::vec3(-0.15f, 0.6f, 0)));
		m_pSquad[2]->AddEnemy(GenerateEnemy(new Goei, glm::vec3(-0.15f, 0.5f, 0)));
		m_pSquad[2]->AddEnemy(GenerateEnemy(new Boss1, glm::vec3(-0.05f, 0.6f, 0)));
		m_pSquad[2]->AddEnemy(GenerateEnemy(new Goei, glm::vec3(-0.15f, 0.4f, 0)));
		m_pSquad[2]->AddEnemy(GenerateEnemy(new Boss1, glm::vec3(0.05f, 0.6f, 0)));
		m_pSquad[2]->AddEnemy(GenerateEnemy(new Goei, glm::vec3(0.15f, 0.5f, 0)));
		m_pSquad[2]->AddEnemy(GenerateEnemy(new Boss1, glm::vec3(0.15f, 0.6f, 0)));
		m_pSquad[2]->AddEnemy(GenerateEnemy(new Goei, glm::vec3(0.15f, 0.4f, 0)));
		m_pSquad[2]->SetSpawnPoint(glm::vec3(-1.2f, -1.2f, 0));
		m_pSquad[2]->SetDelayTime(3.5f);

		pattern = MovePattern();
		pattern.AddPattern(glm::vec3(0, 0, -45), 0.1f);
		pattern.AddPattern(glm::vec3(0, 0, 0), 0.5f);
		pattern.AddPattern(glm::vec3(0, 0, 45), 0.5f);
		pattern.AddPattern(glm::vec3(0, 0, 360), 0.7f);
		pattern.AddPattern(glm::vec3(0, 0, -20), 0.1f);
		m_pSquad[3] = new Squad_(pattern);
		m_pSquad[3]->AddEnemy(GenerateEnemy(new Goei, glm::vec3(0.35f, 0.5f, 0)));
		m_pSquad[3]->AddEnemy(GenerateEnemy(new Goei, glm::vec3(0.25f, 0.5f, 0)));
		m_pSquad[3]->AddEnemy(GenerateEnemy(new Goei, glm::vec3(0.35f, 0.4f, 0)));
		m_pSquad[3]->AddEnemy(GenerateEnemy(new Goei, glm::vec3(0.25f, 0.4f, 0)));
		m_pSquad[3]->AddEnemy(GenerateEnemy(new Goei, glm::vec3(-0.35f, 0.5f, 0)));
		m_pSquad[3]->AddEnemy(GenerateEnemy(new Goei, glm::vec3(-0.25f, 0.5f, 0)));
		m_pSquad[3]->AddEnemy(GenerateEnemy(new Goei, glm::vec3(-0.35f, 0.4f, 0)));
		m_pSquad[3]->AddEnemy(GenerateEnemy(new Goei, glm::vec3(-0.25f, 0.4f, 0)));
		m_pSquad[3]->SetSpawnPoint(glm::vec3(1.2f, -1.2f, 0));
		m_pSquad[3]->SetDelayTime(6.0f);


		pattern = MovePattern();
		pattern.AddPattern(glm::vec3(0, 0, 180), 0.1f);
		pattern.AddPattern(glm::vec3(0, 0, 45), 1.0f);
		pattern.AddPattern(glm::vec3(0, 0, 0), 0.5f);
		pattern.AddPattern(glm::vec3(0, 0, -240), 0.7f);
		pattern.AddPattern(glm::vec3(0, 0, 40), 0.3f);
		m_pSquad[4] = new Squad_(pattern);
		m_pSquad[4]->AddEnemy(GenerateEnemy(new Jako, glm::vec3(-0.15f, 0.3f, 0)));
		m_pSquad[4]->AddEnemy(GenerateEnemy(new Jako, glm::vec3(0.15f, 0.3f, 0)));
		m_pSquad[4]->AddEnemy(GenerateEnemy(new Jako, glm::vec3(-0.15f, 0.2f, 0)));
		m_pSquad[4]->AddEnemy(GenerateEnemy(new Jako, glm::vec3(0.15f, 0.2f, 0)));
		m_pSquad[4]->AddEnemy(GenerateEnemy(new Jako, glm::vec3(-0.25f, 0.3f, 0)));
		m_pSquad[4]->AddEnemy(GenerateEnemy(new Jako, glm::vec3(0.25f, 0.3f, 0)));
		m_pSquad[4]->AddEnemy(GenerateEnemy(new Jako, glm::vec3(-0.25f, 0.2f, 0)));
		m_pSquad[4]->AddEnemy(GenerateEnemy(new Jako, glm::vec3(0.25f, 0.2f, 0)));
		m_pSquad[4]->SetSpawnPoint(glm::vec3(0.15f, 1.2f, 0));
		m_pSquad[4]->SetDelayTime(8.0f);

		pattern = MovePattern();
		pattern.AddPattern(glm::vec3(0, 0, -180), 0.1f);
		pattern.AddPattern(glm::vec3(0, 0, -45), 1.0f);
		pattern.AddPattern(glm::vec3(0, 0, 0), 0.5f);
		pattern.AddPattern(glm::vec3(0, 0, 240), 0.7f);
		pattern.AddPattern(glm::vec3(0, 0, -40), 0.3f);
		m_pSquad[4] = new Squad_(pattern);
		m_pSquad[4]->AddEnemy(GenerateEnemy(new Jako, glm::vec3(-0.35f, 0.3f, 0)));
		m_pSquad[4]->AddEnemy(GenerateEnemy(new Jako, glm::vec3(0.35f, 0.3f, 0)));
		m_pSquad[4]->AddEnemy(GenerateEnemy(new Jako, glm::vec3(-0.35f, 0.2f, 0)));
		m_pSquad[4]->AddEnemy(GenerateEnemy(new Jako, glm::vec3(0.35f, 0.2f, 0)));
		m_pSquad[4]->AddEnemy(GenerateEnemy(new Jako, glm::vec3(-0.45f, 0.3f, 0)));
		m_pSquad[4]->AddEnemy(GenerateEnemy(new Jako, glm::vec3(0.45f, 0.3f, 0)));
		m_pSquad[4]->AddEnemy(GenerateEnemy(new Jako, glm::vec3(-0.45f, 0.2f, 0)));
		m_pSquad[4]->AddEnemy(GenerateEnemy(new Jako, glm::vec3(0.45f, 0.2f, 0)));
		m_pSquad[4]->SetSpawnPoint(glm::vec3(-0.15f, 1.2f, 0));
		m_pSquad[4]->SetDelayTime(10.0f);


	//	break;
	//}
	//case 2:
	//	pattern = MovePattern();
	//	pattern.AddPattern(glm::vec3(0, 0, 180), 0.1f);
	//	pattern.AddPattern(glm::vec3(0, 0, 60), 2.0f);
	//	pattern.AddPattern(glm::vec3(0, 0, 360), 1.0f);
	//	pattern.AddPattern(glm::vec3(0, 0, -250), 2.0f);

	//	m_pSquad[0] = new Squad_(pattern);
	//	m_pSquad[0]->AddEnemy(GenerateEnemy(new Jako, glm::vec3(-0.05f, 0.3f, 0)));
	//	m_pSquad[0]->AddEnemy(GenerateEnemy(new Jako, glm::vec3(0.05f, 0.3f, 0)));
	//	m_pSquad[0]->AddEnemy(GenerateEnemy(new Jako, glm::vec3(0.15f, 0.3f, 0)));
	//	m_pSquad[0]->AddEnemy(GenerateEnemy(new Jako, glm::vec3(-0.15f, 0.3f, 0)));
	//	m_pSquad[0]->AddEnemy(GenerateEnemy(new Jako, glm::vec3(-0.05f, 0.2f, 0)));
	//	m_pSquad[0]->AddEnemy(GenerateEnemy(new Jako, glm::vec3(0.05f, 0.2f, 0)));
	//	m_pSquad[0]->AddEnemy(GenerateEnemy(new Jako, glm::vec3(0.15f, 0.2f, 0)));
	//	m_pSquad[0]->AddEnemy(GenerateEnemy(new Jako, glm::vec3(-0.15f, 0.2f, 0)));
	//	m_pSquad[0]->SetSpawnPoint(glm::vec3(0.2f, 1.2f, 0));

	//	m_pSquad[1] = new Squad_(pattern);
	//	m_pSquad[1]->AddEnemy(GenerateEnemy(new Goei, glm::vec3(-0.05f, 0.5f, 0)));
	//	m_pSquad[1]->AddEnemy(GenerateEnemy(new Goei, glm::vec3(0.05f, 0.5f, 0)));
	//	m_pSquad[1]->AddEnemy(GenerateEnemy(new Goei, glm::vec3(0.15f, 0.5f, 0)));
	//	m_pSquad[1]->AddEnemy(GenerateEnemy(new Goei, glm::vec3(-0.15f, 0.5f, 0)));
	//	m_pSquad[1]->AddEnemy(GenerateEnemy(new Goei, glm::vec3(-0.05f, 0.4f, 0)));
	//	m_pSquad[1]->AddEnemy(GenerateEnemy(new Goei, glm::vec3(0.05f, 0.4f, 0)));
	//	m_pSquad[1]->AddEnemy(GenerateEnemy(new Goei, glm::vec3(0.15f, 0.4f, 0)));
	//	m_pSquad[1]->AddEnemy(GenerateEnemy(new Goei, glm::vec3(-0.15f, 0.4f, 0)));
	//	m_pSquad[1]->SetSpawnPoint(glm::vec3(0.3f, 1.2f, 0));

	//	pattern = MovePattern();
	//	pattern.AddPattern(glm::vec3(0, 0, 90), 0.1f);
	//	pattern.AddPattern(glm::vec3(0, 0, -45), 1.0f);
	//	pattern.AddPattern(glm::vec3(0, 0, 0), 0.5f);
	//	pattern.AddPattern(glm::vec3(0, 0, 240), 0.7f);
	//	pattern.AddPattern(glm::vec3(0, 0, -40), 0.3f);
	//	m_pSquad[2] = new Squad_(pattern);
	//	m_pSquad[2]->AddEnemy(GenerateEnemy(new Goei, glm::vec3(-0.05f, 0.5f, 0)));
	//	m_pSquad[2]->AddEnemy(GenerateEnemy(new Goei, glm::vec3(0.05f, 0.5f, 0)));
	//	m_pSquad[2]->AddEnemy(GenerateEnemy(new Goei, glm::vec3(-0.05f, 0.4f, 0)));
	//	m_pSquad[2]->AddEnemy(GenerateEnemy(new Goei, glm::vec3(0.05f, 0.4f, 0)));
	//	m_pSquad[2]->SetSpawnPoint(glm::vec3(-1.2f, 0.6f, 0));


	//	break;
	//default:
	//	break;
	//}
}

// Release 하면 안됨. Squad내에 적이 없으면 스스로 삭제하기 때문. 그리고 클리어하는 조건이 적이 없어야 하기때문에 100% 이미 없어졌을 것.
//void Stage::ReleaseStage()
//{
//	for (int i = 0; i < SQUAD_SIZE; ++i)
//		if (m_pSquad[i] != nullptr)
//		{
//			m_pSquad[i]->Release();
//			delete m_pSquad[i];
//			m_pSquad[i] = nullptr;
//		}
//}