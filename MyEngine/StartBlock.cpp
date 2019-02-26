#include "StartBlock.h"
#include "MinerTestScene.h"



StartBlock::StartBlock()
{
	SetName("StartBlock");
	m_hp = 1.0f;
}


StartBlock::~StartBlock()
{
}


void StartBlock::Initialize()
{
	Block::Initialize();

	m_pImage->SetSprite("StartBlock");
}


void StartBlock::Destory()
{
	Block::Destory();
	MinerTestScene::GameStart();
}