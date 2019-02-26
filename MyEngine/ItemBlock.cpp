#include "ItemBlock.h"



ItemBlock::ItemBlock()
{
	SetName("ItemBlock");
	SetTag("Item");

	m_pRigid = nullptr;
	m_hp = 1.0f;
}


ItemBlock::~ItemBlock()
{
}



void ItemBlock::Initialize()
{
	Block::Initialize();
	m_pRigid = transform.AddComponent<RigidBody2D>();
	m_pRigid->FreezeRotation(true);
	m_pRigid->SetGravity(false);
}


void ItemBlock::Start()
{
	transform.SetScale(glm::vec3(1.0f));
	transform.SetPositionZ(LAYER_BLOCK);
	m_pCollider->SetHeight(m_pImage->GetCoordHeight());
	m_pCollider->SetWidth(m_pImage->GetCoordWidth());
}


void ItemBlock::Update()
{
	Block::Update();
}


void ItemBlock::Release()
{
	Block::Release();
}