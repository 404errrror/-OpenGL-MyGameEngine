#pragma once
#include "Box2D\Dynamics\b2WorldCallbacks.h"
class MyContactListener :
	public b2ContactListener
{
public:
	MyContactListener();
	~MyContactListener();

	void BeginContact(b2Contact* contant) override;
	void EndContact(b2Contact* contact) override;
};

