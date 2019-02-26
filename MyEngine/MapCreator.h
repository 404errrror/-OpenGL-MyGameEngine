#pragma once
#include "GameObject.h"
#include "Block.h"
class M_Player;
class BlockWeight
{
public:
	int empty;
	int ground;
	int explosion;
	int attackItem;
	int rangeItem;
	int speedItem;
	int allWeight;

	int GetWeight(Block::BlockID blockID);
};

class MapCreator :
	public GameObject
{
public:

	static MapCreator* instance;
	enum Direction
	{
		Top,Bottom,Left,Right
	};
public:
	MapCreator();
	~MapCreator();

	virtual void Initialize();
	virtual void Start();
	virtual void Update();
	virtual void Release();

	void RemoveGrabage();
private:
	glm::ivec2 m_centerPosition;
	std::list<glm::ivec2> genPositionList;
	M_Player* player;

	int height =20;
	int width = 24;

	BlockWeight m_blockWeight[1000];
private:
	void GenerateMap(glm::ivec2 centerPoint);
	void GenerateMapStartPoint();
	void GenerateBlock(glm::ivec2 point, Block::BlockID blockID);
	void GenerateRandomBlock(glm::ivec2 point);
	void GenerateBlockWeight();

	void GenerateGun(glm::ivec2 point);

	void GeneratePattern(glm::ivec2 point, int num, MapCreator::Direction dir);
};

