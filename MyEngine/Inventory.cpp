#include "Inventory.h"
#include "Item.h"

Inventory* Inventory::instance;

Inventory::Inventory()
{
	if (instance == nullptr)
	{
		instance = this;
	}
	else
	{
		m_remove = true;
		return;
	}

	SetName("Inventory");
	for (int i = 0; i < ITEM_HEIGHT; ++i)
		for (int j = 0; j < ITEM_WIDTH; ++j)
			m_pSlot[i][j] = nullptr;

	m_pImage = nullptr;
	m_isVisible = false;
}


Inventory::~Inventory()
{
}


void Inventory::Initialize()
{
	GameObject::Initialize();
	m_pImage = transform.AddComponent<Image>();
	m_pImage->SetSprite("InventoryFrame");

	for (int i = 0; i < ITEM_HEIGHT; ++i)
		for (int j = 0; j < ITEM_WIDTH; ++j)
			m_pSlot[j][i] = new InventorySlot();
	for (int i = 0; i < 8; ++i)
		m_pQuitSlot[i] = new InventorySlot();
}


void Inventory::Start()
{
	GameObject::Start();
	transform.SetPositionZ(LAYER_UI + 0.05f);

	InventorySlotLocate();
	transform.SetPosition(transform.GetPosition().x, -10);

}


void Inventory::Update()
{
	GameObject::Update();
	MoveAnimation();
	KeyInput();
}


void Inventory::Release()
{
	GameObject::Release();
}


bool Inventory::AddItem(Item* item)
{
	for (int y = ITEM_HEIGHT - 1; y >= 0 ; --y)			// 위에서부터 아래로 가야하기 때문에.
		for (int x = 0; x < ITEM_WIDTH; ++x)
			if (m_pSlot[x][y]->AddItem(item))
				return true;
	return false;
}


Item* Inventory::GetQuitItem(int slotId)
{
	if (slotId >= 9 || slotId <= 0)
		return nullptr;
	else
	{
		return m_pQuitSlot[slotId - 1]->GetItem();
	}
}


void Inventory::MoveAnimation()
{
	if (m_isVisible)
	{
		if (transform.GetPosition().y < 0)
		{
			transform.Translate(glm::vec3(0, Time::GetDeltaTime() * 30, 0), true);
			if (transform.GetPosition().y > 0)
				transform.SetPosition(transform.GetPosition().x, 0);
		}

		if (m_pQuitSlot[0]->transform.GetPosition().x < m_quitSlotPosX)
		{
			for(int i = 0; i < 4; ++i)
				m_pQuitSlot[i]->transform.Translate(glm::vec3(Time::GetDeltaTime() * 10, 0, 0), true);
			for (int i = 4; i < 8; ++i)
				m_pQuitSlot[i]->transform.Translate(glm::vec3(-Time::GetDeltaTime() * 10, 0, 0), true);

			if (m_pQuitSlot[0]->transform.GetPosition().x > m_quitSlotPosX)
			{
				for (int i = 0; i < 4; ++i)
					m_pQuitSlot[i]->transform.SetPosition(m_quitSlotPosX, m_pQuitSlot[i]->transform.GetPosition().y);
				for (int i = 4; i < 8; ++i)
					m_pQuitSlot[i]->transform.SetPosition(-m_quitSlotPosX, m_pQuitSlot[i]->transform.GetPosition().y);
			}
		}
	}
	else
	{
		if (transform.GetPosition().y > -10)
		{
			transform.Translate(glm::vec3(0, -Time::GetDeltaTime() * 30, 0), true);
			if (transform.GetPosition().y < -10)
				transform.SetPosition(transform.GetPosition().x,-10);
		}

		if (m_pQuitSlot[0]->transform.GetPosition().x > -9.0f)
		{
			for (int i = 0; i < 4; ++i)
				m_pQuitSlot[i]->transform.Translate(glm::vec3(-Time::GetDeltaTime() * 10, 0, 0), true);
			for (int i = 4; i < 8; ++i)
				m_pQuitSlot[i]->transform.Translate(glm::vec3(Time::GetDeltaTime() * 10, 0, 0), true);

			if (m_pQuitSlot[0]->transform.GetPosition().x < -9.0f)
			{
				for (int i = 0; i < 4; ++i)
					m_pQuitSlot[i]->transform.SetPosition(-9.0f, m_pQuitSlot[i]->transform.GetPosition().y);
				for (int i = 4; i < 8; ++i)
					m_pQuitSlot[i]->transform.SetPosition(9.0f, m_pQuitSlot[i]->transform.GetPosition().y);
			}
		}
	}
}


void Inventory::KeyInput()
{
	if (InputManager::IsKeyDownOnce(GLFW_KEY_I))
		m_isVisible = !m_isVisible;
}


void Inventory::InventorySlotLocate()
{
	glm::vec3 leftBottom = transform.GetPosition() - glm::vec3(m_pImage->GetCoordWidth() * 0.5f, m_pImage->GetCoordHeight() * 0.5f, 0.0f);

	float paddingX = 0.2f;
	float paddingY = 0.2f;

	float spaceWidth = (m_pImage->GetCoordWidth() - paddingX * 2.0f) / ITEM_WIDTH;
	float spaceHeight = (m_pImage->GetCoordHeight() - paddingY * 2.0f) / ITEM_HEIGHT;

	float pivotPosX = leftBottom.x + paddingX + spaceWidth * 0.5f;
	float pivotPosY = leftBottom.y + paddingY + spaceHeight* 0.5f;

	for (int y = 0; y < ITEM_HEIGHT; ++y)
	{
		for (int x = 0; x < ITEM_WIDTH; ++x)
		{
			m_pSlot[x][y]->transform.SetParent(transform);
			m_pSlot[x][y]->transform.SetLocalPosition(
				pivotPosX + x * spaceWidth, 
				pivotPosY + y * spaceHeight
			);
		}
	}


	// Quit Slot
	glm::vec3 leftTop = glm::vec3(-g_coordWidth * 0.5f, g_coordHeight * 0.5f ,0.0f);

	paddingX = -5.5f;
	paddingY = 2.0f;

	spaceWidth = (g_coordWidth - paddingX * 2.0f) / 2;
	spaceHeight = (g_coordHeight - paddingY * 2.0f) / 4;

	pivotPosX = leftTop.x + paddingX + spaceWidth * 0.5f;
	pivotPosY = leftTop.y - paddingY - spaceHeight* 0.5f;

	m_quitSlotPosX = pivotPosX;
	for (int x = 0; x < 2; ++x)
	{
		for (int y = 0; y < 4; ++y)
		{
			if(x == 0)
			m_pQuitSlot[x * 4 + y]->transform.SetPosition(
				-9.0f, 
				pivotPosY - y * spaceHeight);
			else
				m_pQuitSlot[x * 4 + y]->transform.SetPosition(
					9.0f,
					pivotPosY - y * spaceHeight);
		}
	}
}
