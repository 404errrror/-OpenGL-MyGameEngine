#pragma once
#include "Global.h"
class HittedManager
{
public: 
	static std::list<BoxCollider*> activeList;
	static std::list<BoxCollider*> inactiveList;
public:
	HittedManager();
	~HittedManager();

	static void Release();
	static void Update();
	static void Culling();
	static void Add(BoxCollider* pCollider);
	static void Remove(BoxCollider* pCollider);


};

