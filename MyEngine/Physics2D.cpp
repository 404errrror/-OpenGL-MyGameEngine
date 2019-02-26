#include "Physics2D.h"
#include "GameObject.h"
#include "Block.h"

b2World*	Physics2D::pPhysicsWorld;
b2Vec2		Physics2D::gravity;
float		Physics2D::accumulator = 0;
int			Physics2D::stepCount = 0;
const float Physics2D::fixedTime = 1.0f / 60.0f;
MyContactListener Physics2D::myContactListener;
Physics2D::Physics2D()
{
	gravity = b2Vec2(0.0f,0.0f);
	pPhysicsWorld = nullptr;
}


Physics2D::~Physics2D()
{
}


void Physics2D::Initialize()
{
	gravity = b2Vec2(0, -9.81f * METER_PER_UNIT);

	pPhysicsWorld = new b2World(gravity);
	pPhysicsWorld->SetAllowSleeping(true);				// 물체가 정지 했을 때 연산을 안함
	pPhysicsWorld->SetContinuousPhysics(true);			// 지속적으로 충돌 감지
	pPhysicsWorld->SetContactListener(&myContactListener);
}


void Physics2D::Update()
{
	stepCount = 0;
	//gravity = b2Vec2(0, -9.81f * g_pixelPerUnit * Time::GetDeltaTime() * 10.0f);
	//pPhysicsWorld->SetGravity(gravity);
	accumulator += Time::GetDeltaTime();

	while (accumulator > fixedTime)
	{
		pPhysicsWorld->Step(fixedTime, 8, 3);
		accumulator -= fixedTime;
		++stepCount;
	}
}


b2World* Physics2D::GetPhysicsWorld()
{
	return pPhysicsWorld;
}


b2Body* Physics2D::CreateBody(b2BodyDef& def)
{
	return pPhysicsWorld->CreateBody(&def);
}


void Physics2D::DestoryBody(b2Body* body)
{
	pPhysicsWorld->DestroyBody(body);
	body = nullptr;
}


void Physics2D::DrawLine(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{

}


RayCastHit* Physics2D::Raycast(glm::vec2 startPoint, glm::vec2 endPoint)
{
	RayCastHit* result = new RayCastHit();
	b2Vec2 b2StartPoint = b2Vec2(startPoint.x, startPoint.y);
	b2Vec2 b2EndPoint = b2Vec2(endPoint.x, endPoint.y);

	// Rascast
	b2RayCastInput rayInput;
	rayInput.p1 = b2StartPoint;
	rayInput.p2 = b2EndPoint;
	rayInput.maxFraction = 1;

	float closestFraction = 1;
	for (b2Body* b = Physics2D::GetPhysicsWorld()->GetBodyList(); b; b = b->GetNext()) {
		GameObject* m_pGameObject = (GameObject*)b->GetUserData();
		BoxCollider* m_pCollider = nullptr;
		if (m_pGameObject != nullptr)
			m_pCollider = m_pGameObject->transform.GetComponent<BoxCollider>();
		else
			continue;
		if (m_pGameObject->m_active == false || m_pCollider == nullptr || m_pCollider->m_enable == false || m_pCollider->GetIgnoreRaycast() == true)
			continue;
		for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext()) {

			b2RayCastOutput rayOutput;
			if (!f->RayCast(&rayOutput, rayInput, 0))
				continue;
			if (rayOutput.fraction < closestFraction) {
				closestFraction = rayOutput.fraction;
				result->normal = glm::vec2(rayOutput.normal.x, rayOutput.normal.y);
				result->hitObject = (GameObject*)b->GetUserData();
			}
		}
	}
	b2Vec2 intersectionPoint = b2StartPoint + closestFraction * (b2EndPoint - b2StartPoint);

	result->startPoint = glm::vec2(b2StartPoint.x, b2StartPoint.y);
	result->endPoint = glm::vec2(intersectionPoint.x, intersectionPoint.y);
	result->distance = glm::distance(result->startPoint, result->endPoint);

	return result;
}


RayCastHit* Physics2D::Raycast(glm::vec2 startPoint, glm::vec2 endPoint, std::list<BoxCollider*> colliderList)
{
	RayCastHit* result = new RayCastHit();
	result->hitObject = nullptr;
	b2Vec2 b2StartPoint = b2Vec2(startPoint.x, startPoint.y);
	b2Vec2 b2EndPoint = b2Vec2(endPoint.x, endPoint.y);

	// Rascast
	b2RayCastInput rayInput;
	rayInput.p1 = b2StartPoint;
	rayInput.p2 = b2EndPoint;
	rayInput.maxFraction = 1;

	float closestFraction = 1;
	//for (b2Body* b = Physics2D::GetPhysicsWorld()->GetBodyList(); b; b = b->GetNext()) {
	for (std::list<BoxCollider*>::iterator it = colliderList.begin(); it != colliderList.end(); ++it) {
		b2Body* b = (*it)->gameObject.GetPhysicsBody();
			GameObject* m_pGameObject = (GameObject*)b->GetUserData();
		BoxCollider* m_pCollider = nullptr;
		if (m_pGameObject != nullptr)
			m_pCollider = m_pGameObject->transform.GetComponent<BoxCollider>();
		else
			continue;
		if (m_pGameObject->m_active == false || m_pCollider == nullptr || m_pCollider->m_enable == false)
			continue;

		for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext()) {

			b2RayCastOutput rayOutput;
			if (!f->RayCast(&rayOutput, rayInput, 0))
				continue;
			if (rayOutput.fraction < closestFraction) {
				closestFraction = rayOutput.fraction;
				result->normal = glm::vec2(rayOutput.normal.x, rayOutput.normal.y);
				result->hitObject = (GameObject*)b->GetUserData();
			}
		}
	}
	b2Vec2 intersectionPoint = b2StartPoint + closestFraction * (b2EndPoint - b2StartPoint);

	result->startPoint = glm::vec2(b2StartPoint.x, b2StartPoint.y);
	result->endPoint = glm::vec2(intersectionPoint.x, intersectionPoint.y);
	result->distance = glm::distance(result->startPoint, result->endPoint);

	return result;
}


RayCastHit* Physics2D::Raycast(glm::vec2 startPoint, glm::vec2 endPoint, std::list<Block*> blockList)
{
	RayCastHit* result = new RayCastHit();
	b2Vec2 b2StartPoint = b2Vec2(startPoint.x, startPoint.y);
	b2Vec2 b2EndPoint = b2Vec2(endPoint.x, endPoint.y);

	// Rascast
	b2RayCastInput rayInput;
	rayInput.p1 = b2StartPoint;
	rayInput.p2 = b2EndPoint;
	rayInput.maxFraction = 1;

	float closestFraction = 1;
	//for (b2Body* b = Physics2D::GetPhysicsWorld()->GetBodyList(); b; b = b->GetNext()) {
	for (std::list<Block*>::iterator it = blockList.begin(); it != blockList.end(); ++it) {
		b2Body* b = (*it)->GetPhysicsBody();
		GameObject* m_pGameObject = (GameObject*)b->GetUserData();
		BoxCollider* m_pCollider = nullptr;
		if (m_pGameObject != nullptr)
			m_pCollider = m_pGameObject->transform.GetComponent<BoxCollider>();
		else
			continue;
		if (m_pGameObject->m_active == false || m_pCollider == nullptr || m_pCollider->m_enable == false)
			continue;
		for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext()) {

			b2RayCastOutput rayOutput;
			if (!f->RayCast(&rayOutput, rayInput, 0))
				continue;
			if (rayOutput.fraction < closestFraction) {
				closestFraction = rayOutput.fraction;
				result->normal = glm::vec2(rayOutput.normal.x, rayOutput.normal.y);
				result->hitObject = (GameObject*)b->GetUserData();
			}
		}
	}
	b2Vec2 intersectionPoint = b2StartPoint + closestFraction * (b2EndPoint - b2StartPoint);

	result->startPoint = glm::vec2(b2StartPoint.x, b2StartPoint.y);
	result->endPoint = glm::vec2(intersectionPoint.x, intersectionPoint.y);
	result->distance = glm::distance(result->startPoint, result->endPoint);

	return result;
}


std::list<RayCastHit*> Physics2D::RaycastPenetrate(glm::vec2 startPoint, glm::vec2 endPoint, std::list<BoxCollider*> blockList)
{
	std::list<RayCastHit*> resultList;
	b2Vec2 b2StartPoint = b2Vec2(startPoint.x, startPoint.y);
	b2Vec2 b2EndPoint = b2Vec2(endPoint.x, endPoint.y);

	// Rascast
	b2RayCastInput rayInput;
	rayInput.p1 = b2StartPoint;
	rayInput.p2 = b2EndPoint;
	rayInput.maxFraction = 1;

	//for (b2Body* b = Physics2D::GetPhysicsWorld()->GetBodyList(); b; b = b->GetNext()) {
	for (std::list<BoxCollider*>::iterator it = blockList.begin(); it != blockList.end(); ++it) {
		b2Body* b = (*it)->gameObject.GetPhysicsBody();
		GameObject* m_pGameObject = (GameObject*)b->GetUserData();
		BoxCollider* m_pCollider = nullptr;

		if (m_pGameObject != nullptr)
			m_pCollider = m_pGameObject->transform.GetComponent<BoxCollider>();
		else
			continue;
		if (m_pGameObject->m_active == false || m_pCollider == nullptr || m_pCollider->m_enable == false)
			continue;
		for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext()) {

			b2RayCastOutput rayOutput;
			if (!f->RayCast(&rayOutput, rayInput, 0))
				continue;
			if (rayOutput.fraction < 1.0f) {
				RayCastHit* result = new RayCastHit();
				result->normal = glm::vec2(rayOutput.normal.x, rayOutput.normal.y);
				result->hitObject = (GameObject*)b->GetUserData();
				b2Vec2 intersectionPoint = b2StartPoint + rayOutput.fraction  * (b2EndPoint - b2StartPoint);

				result->startPoint = glm::vec2(b2StartPoint.x, b2StartPoint.y);
				result->endPoint = glm::vec2(intersectionPoint.x, intersectionPoint.y);
				result->distance = glm::distance(result->startPoint, result->endPoint);

				resultList.push_back(result);

			}
		}
	}


	return resultList;
}


std::list<RayCastHit*> Physics2D::RaycastPenetrate(glm::vec2 startPoint, glm::vec2 endPoint, std::list<Block*> blockList)
{
	std::list<RayCastHit*> resultList;
	b2Vec2 b2StartPoint = b2Vec2(startPoint.x, startPoint.y);
	b2Vec2 b2EndPoint = b2Vec2(endPoint.x, endPoint.y);

	// Rascast
	b2RayCastInput rayInput;
	rayInput.p1 = b2StartPoint;
	rayInput.p2 = b2EndPoint;
	rayInput.maxFraction = 1;

	//for (b2Body* b = Physics2D::GetPhysicsWorld()->GetBodyList(); b; b = b->GetNext()) {
	for (std::list<Block*>::iterator it = blockList.begin(); it != blockList.end(); ++it) {
		b2Body* b = (*it)->GetPhysicsBody();
		GameObject* m_pGameObject = (GameObject*)b->GetUserData();
		BoxCollider* m_pCollider = nullptr;

		if (m_pGameObject != nullptr)
			m_pCollider = m_pGameObject->transform.GetComponent<BoxCollider>();
		else
			continue;
		if (m_pGameObject->m_active == false || m_pCollider == nullptr || m_pCollider->m_enable == false)
			continue;
		for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext()) {

			b2RayCastOutput rayOutput;
			if (!f->RayCast(&rayOutput, rayInput, 0))
				continue;
			if (rayOutput.fraction < 1.0f) {
				RayCastHit* result = new RayCastHit();
				result->normal = glm::vec2(rayOutput.normal.x, rayOutput.normal.y);
				result->hitObject = (GameObject*)b->GetUserData();
				b2Vec2 intersectionPoint = b2StartPoint + rayOutput.fraction  * (b2EndPoint - b2StartPoint);

				result->startPoint = glm::vec2(b2StartPoint.x, b2StartPoint.y);
				result->endPoint = glm::vec2(intersectionPoint.x, intersectionPoint.y);
				result->distance = glm::distance(result->startPoint, result->endPoint);

				resultList.push_back(result);

			}
		}
	}


	return resultList;
}