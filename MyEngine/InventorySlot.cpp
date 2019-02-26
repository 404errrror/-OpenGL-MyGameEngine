#include "InventorySlot.h"

InventorySlot* InventorySlot::downSlot;

InventorySlot::InventorySlot()
{
	m_pImage = nullptr;
	m_pItem = nullptr;
	m_moveItem = false;
	m_itemLocated = false;
	//m_pCount = nullptr;
}


InventorySlot::~InventorySlot()
{
}


void InventorySlot::Initialize()
{
	GameObject::Initialize();
	m_pImage = transform.AddComponent<Image>();
	m_pButton = transform.AddComponent<Button>();

	m_pImage->SetSprite("InventorySlot");
	m_moveItem = false;
}


void InventorySlot::Start()
{
	GameObject::Start();
	transform.SetPositionZ(LAYER_UI + 0.08f);
	m_pButton->SetFunctionPointerDown(std::bind(&InventorySlot::DownSlot, this));
	m_pButton->SetFunctionPointerUp(std::bind(&InventorySlot::UpSlot, this));

}


void InventorySlot::Update()
{
	GameObject::Update();


	if (m_itemRelease == true)
	{
		if (m_itemLocated == false)
			m_pItem->transform.SetPosition(transform.GetPosition().x, transform.GetPosition().y);

		m_moveItem = false;
		m_itemRelease = false;
		downSlot = nullptr;
	}
	if (m_moveItem)
	{
		m_pItem->transform.SetPosition(MouseManager::GetPositionX(), MouseManager::GetPositionY());
		if (MouseManager::GetLeftState() == MouseManager::Up)
			m_itemRelease = true;
	}
}


void InventorySlot::Release()
{
	GameObject::Release();
}


bool InventorySlot::AddItem(Item* pItem)
{
	if (pItem == nullptr)
		return false;
	m_pItem = pItem;

	switch (pItem->GetItemId())
	{
	case 400:
	case 401:
		m_pItem->transform.SetParent(transform);
		m_pItem->transform.SetLocalPosition(glm::vec3(0.0f));
		m_pItem->transform.SetPositionZ(LAYER_UI + 0.1f);
		return true;
		break;
	default:
		break;
	}
}


void InventorySlot::SwapItem(InventorySlot& slot)
{
	Item* tempItem = m_pItem;
	SetItem(slot.GetItem());
	slot.SetItem(tempItem);


	if (m_pItem != nullptr)
	{
		m_pItem->transform.SetPosition(transform.GetPosition().x, transform.GetPosition().y);
	}

}


void InventorySlot::SetItem(Item* item)
{
	if (item != nullptr)
		item->transform.SetParent(transform);
	m_pItem = item;
}

//
//void InventorySlot::SetItemCount(GalagaNumber* count)
//{
//	m_pCount = count;
//}


//GalagaNumber* InventorySlot::GetItemCount()
//{
//	return m_pCount;
//}


Item* InventorySlot::GetItem()
{
	return m_pItem;
}


void InventorySlot::DownSlot()
{
	if (m_pItem != nullptr)
	{
		m_itemLocated = false;
		m_moveItem = true;
		downSlot = this;
	}
}


void InventorySlot::UpSlot()
{
	if (downSlot != nullptr)
	{
		downSlot->m_itemLocated = true;
		SwapItem(*downSlot);
	}
}