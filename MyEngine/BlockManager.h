#pragma once
#include "GameObject.h"
#include "Block.h"

class BlockManager :
	public GameObject
{
public:
	static std::list<Block*> activeList;
	static std::list<Block*> inactiveList;
	static BlockManager* instance;
public:
	BlockManager();
	~BlockManager();

	virtual void Initialize();
	virtual void Start();
	virtual void Update();
	virtual void Release();

private:
	void BlockCulling();

};

