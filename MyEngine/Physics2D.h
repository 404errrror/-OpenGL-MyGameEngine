#pragma once
#include "Global.h"
#include "RayCastHit.h"
#include "MyContactListener.h"

class BoxCollider;
class Block;

class Physics2D
{
public:
	Physics2D();
	~Physics2D();

	static void Initialize();
	static void Update();
	static void Release();

	static b2World* GetPhysicsWorld();
	static b2Body* CreateBody(b2BodyDef& def);
	static void DestoryBody(b2Body* body);

	static void DrawLine(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
	static RayCastHit* Raycast(glm::vec2 startPoint, glm::vec2 endPoint);
	static RayCastHit* Raycast(glm::vec2 startPoint, glm::vec2 endPoint, std::list<BoxCollider*> colliderList); // test안해봄.
	static RayCastHit* Raycast(glm::vec2 startPoint, glm::vec2 endPoint, std::list<Block*> blockList);
	static std::list<RayCastHit*> RaycastPenetrate(glm::vec2 startPoint, glm::vec2 endPoint, std::list<BoxCollider*> blockList);
	static std::list<RayCastHit*> RaycastPenetrate(glm::vec2 startPoint, glm::vec2 endPoint, std::list<Block*> blockList);
public:
	static int	stepCount;
	static const float  fixedTime;

private:
	static b2World* pPhysicsWorld;  //물리 월드
	static MyContactListener myContactListener;	// StartContact, EndContact 설정
	static b2Vec2 gravity;

	static float accumulator;

};

