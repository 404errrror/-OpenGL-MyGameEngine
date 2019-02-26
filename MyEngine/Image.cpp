#include "Image.h"
#include "GameObject.h"
#include "SpriteManager.h"
#include "ShaderManager.h"
#include "CameraC.h"

static GLfloat rectVertex[3 * 2 * 3] = {		// �ﰢ�� �ϳ��� 3�� * �ﰢ�� 2�� * xyz
	-0.5,0.5, 0,
	-0.5,-0.5,0,
	0.5,-0.5,0,
	0.5,-0.5,0,
	0.5,0.5,0,
	-0.5,0.5,0
};


static GLfloat rectUv[] =						// Png�� ���Ϲ����� �Ǳ� ������ ���Ϲ����ǵ��� ����.
{
	0,0,
	0,1,
	1,1,
	1,1,
	1,0,
	0,0
};



std::list<Image*> Image::list;
std::list<Image*> Image::transparentList;

Image::Image(GameObject& gameObject) : Component(gameObject)
{
	list.push_back(this);
	m_pSprite = nullptr;
	m_pShader = ShaderManager::GetShader("ImageShader");

	glGenBuffers(1, &m_vertexID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectVertex), rectVertex, GL_STATIC_DRAW);

	glGenBuffers(1, &m_uvID);
	glBindBuffer(GL_ARRAY_BUFFER, m_uvID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectUv), rectUv, GL_STATIC_DRAW);

	m_MVP_MatrixID = glGetUniformLocation(*m_pShader, "myMatrix");
	m_myColorID = glGetUniformLocation(*m_pShader, "myColor");
	m_isUi = false;
	m_color = glm::vec4(1.0f);

}


Image::~Image()
{
}


void Image::Initialize()
{

}


void Image::Update()
{
	//return;
	if (m_pSprite == nullptr)
	{
		std::cout << "Image::Update() �̹����� ���õǾ����� �ʽ��ϴ�." << std::endl;
		return;
	}

	glm::mat4 resultMatrix;
	resultMatrix = glm::scale(
		glm::vec3(
		(float)m_pSprite->m_width / PIXEL_PER_UNIT, 
		(float)m_pSprite->m_height / PIXEL_PER_UNIT, 
		(float)1 / PIXEL_PER_UNIT)); // �̹��� ũ��

	if (m_isUi == false)
	{
		resultMatrix = CameraC::main->GetPerspectiveVP()* gameObject.transform.GetMatrix() * resultMatrix;
	}
	else
		resultMatrix = CameraC::main->GetOrthoProjection() * gameObject.transform.GetMatrix() * resultMatrix;


	glBindTexture(GL_TEXTURE_2D, m_pSprite->imageId);
	glUseProgram(*m_pShader);
	glUniformMatrix4fv(m_MVP_MatrixID, 1, GL_FALSE, &resultMatrix[0][0]);
	glUniform4f(m_myColorID, m_color.r, m_color.g, m_color.b, m_color.a);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexID);
	glVertexAttribPointer(
		0,                  // 0��° �Ӽ�(attribute). 0 �� �� Ư���� ������ ������, ���̴��� ���̾ƿ�(layout)�� �ݵ�� ���߾�� �մϴ�.
		3,                  // ũ��(size)
		GL_FLOAT,           // Ÿ��(type)
		GL_FALSE,           // ����ȭ(normalized)?
		0,                  // ���� ��� ���� ����(stride)
		(void*)0            // �迭 ������ ������(offset; �ű�� ��)
	);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, m_uvID);
	glVertexAttribPointer(
		1,                  // 0��° �Ӽ�(attribute). 0 �� �� Ư���� ������ ������, ���̴��� ���̾ƿ�(layout)�� �ݵ�� ���߾�� �մϴ�.
		2,                  // ũ��(size)
		GL_FLOAT,           // Ÿ��(type)
		GL_FALSE,           // ����ȭ(normalized)?
		0,                  // ���� ��� ���� ����(stride)
		(void*)0            // �迭 ������ ������(offset; �ű�� ��)
	);

	glDrawArrays(GL_TRIANGLES, 0, 3 * 2 * 3); // ���ؽ� 0���� �����ؼ�; �� 3���� ���ؽ��� -> �ϳ��� �ﰢ��

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);


}


void Image::Release()
{
	Component::Release();

	for (std::list<Image*>::iterator it = list.begin(); it != list.end(); ++it)
	{
		if (this == *it)
		{
			glDeleteBuffers(1, &m_vertexID);
			glDeleteBuffers(1, &m_uvID);
			list.erase(it);
			return;
		}
	}

	for (std::list<Image*>::iterator it = transparentList.begin(); it != transparentList.end(); ++it)
	{
		if (this == *it)
		{
			glDeleteBuffers(1, &m_vertexID);
			glDeleteBuffers(1, &m_uvID);
			transparentList.erase(it);
			return;
		}
	}
}


bool Image::SetSprite(const char* imageKey)
{
	m_pSprite = SpriteManager::GetImagePtr(imageKey);

	//glBindBuffer(GL_ARRAY_BUFFER, m_vertexID);

	//if(m_pSprite->m_hasAlpha)		// ������ �ִٸ�.
	//	for (std::list<Image*>::iterator it = list.begin(); it != list.end(); ++it)
	//	{
	//		if (*it == this)
	//		{
	//			list.erase(it);
	//			transparentList.push_back(this);
	//			break;
	//		}
	//	}
	//else							// ������ ���ٸ�
	//	for (std::list<Image*>::iterator it = transparentList.begin(); it != transparentList.end(); ++it)
	//	{
	//		if (*it == this)
	//		{
	//			transparentList.erase(it);
	//			list.push_back(this);
	//			break;
	//		}
	//	}

	if (m_pSprite == nullptr)
	{
		printf("ImageComponent::SetImage   %s�� �����ϴ�. ImageManager�� ����ߴ��� Ȯ�����ּ���.\n", imageKey);
		return false;
	}
	else
		return true;
}


bool Image::SetSprite(Sprite* sprite)
{
	if (sprite == nullptr)
		return false;
	m_pSprite = sprite;
	return true;
	// ------------> ������ ���� ó��?
}


bool Image::SetSahder(const char* shaderKey)
{
	m_pShader = ShaderManager::GetShader(shaderKey);
	return true;
}


void Image::SetUI(bool isUi)
{
	m_isUi = isUi;
}


void Image::SetColor(glm::vec4 color)
{
	m_color = color;
}


void Image::SetColorAlpha(float alpha)
{
	m_color.a = alpha;
}


float Image::GetWidth()
{
	return m_pSprite->m_width;
}


float Image::GetHeight()
{
	return m_pSprite->m_height;
}


float Image::GetCoordWidth()
{
	return m_pSprite->m_width * gameObject.transform.GetScale().x / PIXEL_PER_UNIT;
}


float Image::GetCoordHeight()
{
	return m_pSprite->m_height * gameObject.transform.GetScale().y / PIXEL_PER_UNIT;
}


Sprite* Image::GetSprite()
{
	return m_pSprite;
}


glm::vec4 Image::GetColor()
{
	return m_color;
}


bool Image::HasAlpha()
{
	if (m_pSprite->m_hasAlpha || m_color.a < 1)
		return true;
	else
		return false;
}


void Image::CalculateVertexPos()
{
	glm::mat4 matrix = gameObject.transform.GetMatrix();
}