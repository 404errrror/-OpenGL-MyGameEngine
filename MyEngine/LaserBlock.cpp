#include "LaserBlock.h"



LaserBlock::LaserBlock()
{
	SetName("LaserBlock");
}


LaserBlock::~LaserBlock()
{
}


void LaserBlock::Initialize()
{
	Block::Initialize();
	m_pLine = transform.AddComponent<Line>();
	m_pLine2 = transform.AddComponent<Line>();
	m_pImage->SetSahder("AddColor");
	m_pImage->SetSprite("LaserBlock_1");
	SetName("LaserBlock");
}


void LaserBlock::Start()
{
	m_pImage->SetColor(glm::vec4(0, 0, 0, 0));
	m_pLine->SetColor(glm::vec4(1.0f, 0.0f, 0.0f, 0.7f));
	m_pLine2->SetColor(glm::vec4(1.0f, 0.0f, 0.0f, 0.7f));
	Block::Start();
}


void LaserBlock::Update()
{
	Block::Update();
	switch (m_laserCount)
	{
	case 1:
		LaserUpdate1();
		break;
	case 2:
		LaserUpdate2();
		break;
	case 3:
		LaserUpdate4();
		break;
	default:
		break;
	}
}


void LaserBlock::SetLaserCount(int num)
{
	m_laserCount = num;
	switch (num)
	{
	case 1:
		m_pImage->SetSprite("LaserBlock_1");
		break;
	case 2:
		m_pImage->SetSprite("LaserBlock_2");
		break;
	case 3:
		m_pImage->SetSprite("LaserBlock_4");
		break;
	default:
		break;
	}
}


void LaserBlock::LaserUpdate1()
{
	RayCastHit* hit;
	glm::vec2 position = glm::vec2(transform.GetPosition().x, transform.GetPosition().y);
	glm::vec2 endPosition;

	if (transform.GetRotation().z == 0.0f)
	{
		hit = Physics2D::Raycast(position, glm::vec2(position.x - 13, position.y));
		if (hit->hitObject == nullptr)
			endPosition = glm::vec2(position.x - 13, position.y);
		else
			endPosition = hit->endPoint;
	}
	else if (transform.GetRotation().z == 90.0f)
	{
		hit = Physics2D::Raycast(position, glm::vec2(position.x, position.y + 13));
		if (hit->hitObject == nullptr)
			endPosition = glm::vec2(position.x, position.y + 13);
		else
			endPosition = hit->endPoint;
	}
	else if (transform.GetRotation().z == 180.0f)
	{
		hit = Physics2D::Raycast(position, glm::vec2(position.x + 13, position.y));
		if (hit->hitObject == nullptr)
			endPosition = glm::vec2(position.x + 13, position.y);
		else
			endPosition = hit->endPoint;
	}
	else
	{
		hit = Physics2D::Raycast(position, glm::vec2(position.x, position.y - 13));
		if (hit->hitObject == nullptr)
			endPosition = glm::vec2(position.x, position.y - 13);
		else
			endPosition = hit->endPoint;
	}

	m_pLine->SetPoint(position, endPosition);

	if (hit->hitObject != nullptr && hit->hitObject->GetName() == "Player")
		hit->hitObject->SendEvent("Die");

	delete hit;
}


void LaserBlock::LaserUpdate2()
{
	RayCastHit* hit1;
	RayCastHit* hit2;
	glm::vec2 position = glm::vec2(transform.GetPosition().x, transform.GetPosition().y);
	glm::vec2 endPosition1, endPosition2;

	if (transform.GetRotation().z == 0.0f)
	{
		hit1 = Physics2D::Raycast(position, glm::vec2(position.x - 13, position.y));
		hit2 = Physics2D::Raycast(position, glm::vec2(position.x + 13, position.y));
		if (hit1->hitObject == nullptr)
			endPosition1 = glm::vec2(position.x - 13, position.y);
		else
			endPosition1 = hit1->endPoint;

		if (hit2->hitObject == nullptr)
			endPosition2 = glm::vec2(position.x + 13, position.y);
		else
			endPosition2 = hit2->endPoint;
	}
	else if (transform.GetRotation().z == 90.0f)
	{
		hit1 = Physics2D::Raycast(position, glm::vec2(position.x, position.y - 13));
		hit2 = Physics2D::Raycast(position, glm::vec2(position.x, position.y + 13));
		if (hit1->hitObject == nullptr)
			endPosition1 = glm::vec2(position.x, position.y - 13);
		else
			endPosition1 = hit1->endPoint;

		if (hit2->hitObject == nullptr)
			endPosition2 = glm::vec2(position.x, position.y + 13);
		else
			endPosition2 = hit2->endPoint;
	}

	m_pLine->SetPoint(endPosition1, endPosition2);

	if (hit1->hitObject != nullptr && hit1->hitObject->GetName() == "Player")
		hit1->hitObject->SendEvent("Die");
	if(hit2->hitObject != nullptr && hit2->hitObject->GetName() == "Player")
		hit2->hitObject->SendEvent("Die");
	delete hit1;
	delete hit2;
}


void LaserBlock::LaserUpdate4()
{
	RayCastHit* hit1;
	RayCastHit* hit2;
	RayCastHit* hit3;
	RayCastHit* hit4;
	glm::vec2 position = glm::vec2(transform.GetPosition().x, transform.GetPosition().y);
	glm::vec2 endPosition1, endPosition2, endPosition3, endPosition4;

	hit1 = Physics2D::Raycast(position, glm::vec2(position.x - 13, position.y));
	hit2 = Physics2D::Raycast(position, glm::vec2(position.x + 13, position.y));
	hit3 = Physics2D::Raycast(position, glm::vec2(position.x, position.y - 13));
	hit4 = Physics2D::Raycast(position, glm::vec2(position.x, position.y + 13));
	if (hit1->hitObject == nullptr)
		endPosition1 = glm::vec2(position.x - 13, position.y);
	else
		endPosition1 = hit1->endPoint;

	if (hit2->hitObject == nullptr)
		endPosition2 = glm::vec2(position.x + 13, position.y);
	else
		endPosition2 = hit2->endPoint;

	if (hit3->hitObject == nullptr)
		endPosition3 = glm::vec2(position.x , position.y - 13);
	else
		endPosition3 = hit3->endPoint;

	if (hit4->hitObject == nullptr)
		endPosition4 = glm::vec2(position.x , position.y + 13);
	else
		endPosition4 = hit4->endPoint;

	m_pLine->SetPoint(endPosition1, endPosition2);
	m_pLine2->SetPoint(endPosition3, endPosition4);

	if (hit1->hitObject != nullptr && hit1->hitObject->GetName() == "Player")
		hit1->hitObject->SendEvent("Die");
	if (hit2->hitObject != nullptr && hit2->hitObject->GetName() == "Player")
		hit2->hitObject->SendEvent("Die");
	if (hit3->hitObject != nullptr && hit3->hitObject->GetName() == "Player")
		hit3->hitObject->SendEvent("Die");
	if (hit4->hitObject != nullptr && hit4->hitObject->GetName() == "Player")
		hit4->hitObject->SendEvent("Die");
	delete hit1;
	delete hit2;
	delete hit3;
	delete hit4;
}