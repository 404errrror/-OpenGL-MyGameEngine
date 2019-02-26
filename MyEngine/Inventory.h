#pragma once
#include "GameObject.h"
#include "InventorySlot.h"
#include <functional>

#define ITEM_WIDTH 6
#define ITEM_HEIGHT 4

class Inventory :
	public GameObject
{
public:
	static Inventory* instance;
public:
	Inventory();
	~Inventory();

	virtual void Initialize();
	virtual void Start();
	virtual void Update();
	virtual void Release();

	bool AddItem(Item* item);
	Item* GetQuitItem(int slotId);

private:
	Image* m_pImage;
	bool m_isVisible;

	InventorySlot* m_pSlot[ITEM_WIDTH][ITEM_HEIGHT];
	InventorySlot* m_pQuitSlot[8];
	float m_quitSlotPosX;

private:
	void MoveAnimation();
	void KeyInput();
	void InventorySlotLocate();

};

