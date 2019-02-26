#pragma once
#include "GameObject.h"
#include "Global.h"
#include "Item.h"

class InventorySlot :
	public GameObject
{
public:
	static InventorySlot* downSlot;
	bool m_itemLocated;

public:
	InventorySlot();
	~InventorySlot();

	virtual void Initialize() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void Release() override;

	bool AddItem(Item* pItem);
	void SwapItem(InventorySlot& slot);

	void SetItem(Item* item);
	//void SetItemCount(GalagaNumber* count);


	Item* GetItem();
	//GalagaNumber* GetItemCount();

private:
	void DownSlot();
	void UpSlot();
private:
	Image* m_pImage;
	//GameObject* m_pItem;
	Button* m_pButton;

	Item* m_pItem;

	bool m_moveItem;
	bool m_itemRelease;
};

