#pragma once
#include "glm\glm.hpp"
class GameObject;
class RayCastHit
{
public:
	RayCastHit();
	~RayCastHit();

	glm::vec2 startPoint;
	glm::vec2 endPoint;
	glm::vec2 normal;
	GameObject* hitObject;
	float distance;
};

