#include "Button.h"
#include "Image.h"
#include "SpriteManager.h"
#include "GameObject.h"

std::list<Button*> Button::list;

Button::Button(GameObject& gameObject): Component(gameObject)
{
	list.push_back(this);
	m_pImage = nullptr;
	m_pSprite = nullptr;
	m_pFocusSprite = nullptr;
	m_pDownSprite = nullptr;

	m_height = m_width = 0;
	m_state = None;

	fp_pointerEnter = nullptr;
	fp_pointerExit = nullptr;
	fp_pointerDown = nullptr;
	fp_pointerRightDown = nullptr;
	fp_pointerUp = nullptr;
	fp_pointerRightUp = nullptr;
	fp_onClick = nullptr;
	fp_onRightClick = nullptr;
}


Button::~Button()
{
}


void Button::Initialize()
{
	Component::Initialize();
	m_pImage = GetComponent<Image>();
	m_pSprite = m_pImage->GetSprite();
	UpdateSprite();
}


void Button::Update()
{
	Component::Update();

	if (m_pImage == nullptr)
	{
		m_pImage = GetComponent<Image>();
		m_pSprite = m_pImage->GetSprite();
		UpdateSprite();
		if (m_pImage == nullptr)
		{
			std::cout << "Button::Update   ImageComponent를 찾을 수 없습니다." << std::endl;
			return;
		}

	}
	else if (m_pSprite == nullptr)
	{
		m_pSprite = m_pImage->GetSprite();
		UpdateSprite();
		if (m_pSprite == nullptr)
		{
			std::cout << "Button::Update   Sprite가 없습니다." << std::endl;
			return;
		}
	}

	glm::vec2 mousePositon = MouseManager::GetPosition();
	glm::vec3 position = gameObject.transform.GetPosition();

	if (position.x + m_width * 0.5f >= mousePositon.x &&	// 버튼 위에 있다면
		position.x - m_width * 0.5f <= mousePositon.x &&
		position.y + m_height * 0.5f >= mousePositon.y &&
		position.y - m_height * 0.5f <= mousePositon.y)
	{
		MouseManager::State leftMouseState = MouseManager::GetLeftState();
		MouseManager::State rightMouseState = MouseManager::GetRightState();
		switch (m_state)
		{
		case Button::None:
			PointerEnter();
			m_state = Enter;



		case Button::Enter:
			if (leftMouseState == MouseManager::State::Press)
			{
				PointerDown();
				m_state = Pressing;
			}
			else if (rightMouseState == MouseManager::State::Press)
			{
				PointerRightDown();
				m_state = RightPressing;
			}
			else if (leftMouseState == MouseManager::State::Up)
			{
				PointerUp();
				m_state = Enter;
			}
			else if (rightMouseState == MouseManager::State::Up)
			{
				PointerRightUp();
				m_state = Enter;
			}
			break;

		case Button::Pressing:
			if (leftMouseState == MouseManager::State::Up)
			{
				PointerUp();
				PointerOnClick();
				m_state = Enter;
			}
			break;

		case Button::RightPressing:
			if (rightMouseState == MouseManager::State::Up)
			{
				PointerRightUp();
				PointerOnRightClick();
				m_state = Enter;
			}
			break;
		default:
			break;
		}

	}
	else													// 버튼 위에 없다면
	{
		if (m_state == Enter || m_state == Pressing || m_state == RightPressing)
			PointerExit();
		m_state = None;
	}
}


void Button::Release()
{
	Component::Release();
	for(std::list<Button*>::iterator it = list.begin(); it != list.end(); ++it)
		if (*it == this)
		{
			list.erase(it);
			return;
		}
}


void Button::PointerEnter()
{
	if (m_pFocusSprite != nullptr)
		m_pImage->SetSprite(m_pFocusSprite);
	else
		m_pImage->SetColor(glm::vec4(0.7f, 0.7f, 0.7f, 1.0f));

	if (fp_pointerEnter != nullptr)
		fp_pointerEnter();
}


void Button::PointerExit()
{
	if (m_pFocusSprite != nullptr)			// FocusSprite를 검사하는게 맞음.
		m_pImage->SetSprite(m_pSprite);
	else
		m_pImage->SetColor(glm::vec4(1.0f));

	if (fp_pointerExit != nullptr)
		fp_pointerExit();
}


void Button::PointerDown()
{
	if (m_pDownSprite != nullptr)
		m_pImage->SetSprite(m_pDownSprite);
	else
		m_pImage->SetColor(glm::vec4(0.4f, 0.4f, 0.4f, 1.0f));

	if (fp_pointerDown != nullptr)
		fp_pointerDown();

}

void Button::PointerRightDown()
{
	if (m_pDownSprite != nullptr)
		m_pImage->SetSprite(m_pDownSprite);
	else
		m_pImage->SetColor(glm::vec4(0.4f, 0.4f, 0.4f, 1.0f));

	if (fp_pointerRightDown != nullptr)
		fp_pointerRightDown();
}


void Button::PointerUp()
{
	if (m_pFocusSprite != nullptr)
		m_pImage->SetSprite(m_pFocusSprite);
	else
		m_pImage->SetColor(glm::vec4(0.7f, 0.7f, 0.7f, 1.0f));

	if (fp_pointerUp != nullptr)
		fp_pointerUp();
}


void Button::PointerRightUp()
{
	if (m_pFocusSprite != nullptr)
		m_pImage->SetSprite(m_pFocusSprite);
	else
		m_pImage->SetColor(glm::vec4(0.7f, 0.7f, 0.7f, 1.0f));

	if (fp_pointerRightUp != nullptr)
		fp_pointerRightUp();
}




void Button::PointerOnClick()
{
	if (fp_onClick != nullptr)
		fp_onClick();

}


void Button::PointerOnRightClick()
{
	if (fp_onRightClick != nullptr)
		fp_onRightClick();

}


void Button::SetSprite(const char* imageKey)
{
	m_pSprite = SpriteManager::GetImagePtr(imageKey);
	UpdateSprite();
}


void Button::SetFocusSprite(const char* imageKey)
{
	m_pFocusSprite = SpriteManager::GetImagePtr(imageKey);
}


void Button::SetDownSprite(const char* imageKey)
{
	m_pDownSprite = SpriteManager::GetImagePtr(imageKey);
}


void Button::SetFunctionPointerEnter(std::function<void(void)> fp)
{
	fp_pointerEnter = fp;
}


void Button::SetFunctionPointerExit(std::function<void(void)> fp)
{
	fp_pointerExit = fp;
}


void Button::SetFunctionPointerDown(std::function<void(void)> fp)
{
	fp_pointerDown = fp;
}


void Button::SetFunctionPointerRightDown(std::function<void(void)> fp)
{
	fp_pointerRightDown = fp;
}


void Button::SetFunctionPointerUp(std::function<void(void)> fp)
{
	fp_pointerUp = fp;
}


void Button::SetFunctionPointerRightUp(std::function<void(void)> fp)
{
	fp_pointerRightUp = fp;
}



void Button::SetFunctionOnClick(std::function<void(void)> fp)
{
	fp_onClick = fp;
}


void Button::SetFunctionOnRightClick(std::function<void(void)> fp)
{
	fp_onRightClick = fp;
}


void Button::UpdateSprite()
{
	if (m_pImage != nullptr && m_pSprite != nullptr)
	{
		m_width = m_pImage->GetCoordWidth();
		m_height = m_pImage->GetCoordHeight();
	}
}