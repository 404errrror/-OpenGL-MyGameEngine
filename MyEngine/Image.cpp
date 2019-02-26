#include "Image.h"
#include "GameObject.h"
#include "SpriteManager.h"
#include "ShaderManager.h"
#include "CameraC.h"

static GLfloat rectVertex[3 * 2 * 3] = {		// 삼각형 하나당 3개 * 삼각형 2개 * xyz
	-0.5,0.5, 0,
	-0.5,-0.5,0,
	0.5,-0.5,0,
	0.5,-0.5,0,
	0.5,0.5,0,
	-0.5,0.5,0
};


static GLfloat rectUv[] =						// Png는 상하반전이 되기 때문에 상하반전되도록 매핑.
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
		std::cout << "Image::Update() 이미지가 셋팅되어있지 않습니다." << std::endl;
		return;
	}

	glm::mat4 resultMatrix;
	resultMatrix = glm::scale(
		glm::vec3(
		(float)m_pSprite->m_width / PIXEL_PER_UNIT, 
		(float)m_pSprite->m_height / PIXEL_PER_UNIT, 
		(float)1 / PIXEL_PER_UNIT)); // 이미지 크기

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
		0,                  // 0번째 속성(attribute). 0 이 될 특별한 이유는 없지만, 쉐이더의 레이아웃(layout)와 반드시 맞추어야 합니다.
		3,                  // 크기(size)
		GL_FLOAT,           // 타입(type)
		GL_FALSE,           // 정규화(normalized)?
		0,                  // 다음 요소 까지 간격(stride)
		(void*)0            // 배열 버퍼의 오프셋(offset; 옮기는 값)
	);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, m_uvID);
	glVertexAttribPointer(
		1,                  // 0번째 속성(attribute). 0 이 될 특별한 이유는 없지만, 쉐이더의 레이아웃(layout)와 반드시 맞추어야 합니다.
		2,                  // 크기(size)
		GL_FLOAT,           // 타입(type)
		GL_FALSE,           // 정규화(normalized)?
		0,                  // 다음 요소 까지 간격(stride)
		(void*)0            // 배열 버퍼의 오프셋(offset; 옮기는 값)
	);

	glDrawArrays(GL_TRIANGLES, 0, 3 * 2 * 3); // 버텍스 0에서 시작해서; 총 3개의 버텍스로 -> 하나의 삼각형

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

	//if(m_pSprite->m_hasAlpha)		// 투명도가 있다면.
	//	for (std::list<Image*>::iterator it = list.begin(); it != list.end(); ++it)
	//	{
	//		if (*it == this)
	//		{
	//			list.erase(it);
	//			transparentList.push_back(this);
	//			break;
	//		}
	//	}
	//else							// 투명도가 없다면
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
		printf("ImageComponent::SetImage   %s가 없습니다. ImageManager에 등록했는지 확인해주세요.\n", imageKey);
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
	// ------------> 투명도에 따른 처리?
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