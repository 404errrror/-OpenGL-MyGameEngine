#include "GalagaNumber.h"
#include "Image.h"
#include <math.h>


GalagaNumber::GalagaNumber()
{
	SetName("GalagaNumber");
	m_data = 0;
	m_length = 1;
	m_pImage = nullptr;
	m_aligh = Left;
}


GalagaNumber::~GalagaNumber()
{
}


void GalagaNumber::Initialize()
{
	GameObject::Initialize();
	m_pImage = transform.AddComponent<Image>();
	m_pImage->m_enable = false;			// 수동으로 업데이트 할 것이기 때문에.
	m_aligh = Left;
}


void GalagaNumber::Start()
{
	GameObject::Start();
	//transform.SetScale(glm::vec3(0.08f, 0.08f, 0.08f));
}


void GalagaNumber::Update()
{
	if (m_isStart == false)
		Start();

	m_tempPosition = transform.GetPosition();

	if (m_aligh == Left)
	{
		for (int i = 0; i < m_dataString.length(); ++i)
		{
			std::string str = "Font_";
			str += m_dataString[i];

			m_pImage->SetSprite(str.c_str());
			transform.SetPosition(glm::vec3(
				m_tempPosition.x + i * transform.GetScale().x * 0.3f,
				m_tempPosition.y, m_tempPosition.z
			));
			m_pImage->Update();
		}
		if (m_spriteKey.length() != 0)
		{
			transform.SetPosition(glm::vec3(
				m_tempPosition.x + m_dataString.length() * transform.GetScale().x * 0.3f,
				m_tempPosition.y, m_tempPosition.z
			));
			m_pImage->SetSprite(m_spriteKey.c_str());
			m_pImage->Update();
		}
	}
	else if (m_aligh == Right)
	{
		for (int i = 0; i < m_dataString.length(); ++i)
		{
			std::string str = "Font_";
			str += m_dataString[m_dataString.length() - 1 - i];

			m_pImage->SetSprite(str.c_str());
			transform.SetPosition(glm::vec3(
				m_tempPosition.x - i * transform.GetScale().x * 0.3f,
				m_tempPosition.y, m_tempPosition.z
			));
			m_pImage->Update();
		}
		if (m_spriteKey.length() != 0)
		{
			transform.SetPosition(glm::vec3(
				m_tempPosition.x - m_dataString.length() * transform.GetScale().x * 0.3f,
				m_tempPosition.y, m_tempPosition.z
			));
			m_pImage->SetSprite(m_spriteKey.c_str());
			m_pImage->Update();
		}
	}

	transform.SetPosition(m_tempPosition);
}


void GalagaNumber::Release()
{
	GameObject::Release();
}


int GalagaNumber::operator=(int data)
{
	m_data = data;
	UpdateData();
	return m_data;
}


int GalagaNumber::operator+(int data)
{
	return m_data + data;
}


int GalagaNumber::operator-(int data)
{
	return m_data - data;
}


int GalagaNumber::operator+=(int data)
{
	m_data = m_data + data;
	UpdateData();
	return m_data;
}


int GalagaNumber::operator++()
{
	int temp = m_data;
	++m_data;
	UpdateData();
	return temp;
}


void GalagaNumber::SetAligh(Aligh aligh)
{
	m_aligh = aligh;
}


void GalagaNumber::SetUnit(const char* spriteKey)
{
	m_spriteKey = spriteKey;
}


void GalagaNumber::SetColor(glm::vec4 color)
{
	m_pImage->SetColor(color);
}


int GalagaNumber::GetData()
{
	return m_data;
}


void GalagaNumber::UpdateData()
{
	//m_length = GetLength();
	char temp[32];
	sprintf(temp, "%d", m_data);

	m_dataString = temp;
}


int GalagaNumber::GetLength()
{
	int data = m_data;
	//int length = 0;
	//for (;;)
	//{
	//	data = data * 0.1f;
	//	if (data != 0)
	//	{
	//		++length;
	//	}
	//	else
	//		return length;
	//}

	char* temp;
	sprintf(temp, "%d", m_data);

	m_dataString = temp;

	return 0;
}