#pragma once
#include "Component.h"
#include "Sprite.h"
class GameObject;
class Image :
	public Component
{
public:
	static std::list<Image*> list;
	static std::list<Image*> transparentList;


public:
	Image(GameObject& gameObject);
	~Image();

	void Initialize()	override;
	void Update()		override;
	void Release()		override;

	/// <summary>
	/// 이미지를 셋팅합니다.
	/// </summary>
	bool		SetSprite(const char* imageKey);
	bool		SetSprite(Sprite* sprite);
	/// <summary>
	/// 쉐이더를 셋팅합니다
	/// </summary>
	bool		SetSahder(const char* shaderKey);

	/// <summary>
	/// false로 설정하면 카메라에 영향을 받지 않습니다.
	/// </summary>
	void SetUI(bool isUi);
	/// <summary>
	/// 색깔을 설정합니다. Unity의 color와 같은 기능을 합니다.
	/// </summary>
	void SetColor(glm::vec4 color);
	void SetColorAlpha(float alpha);

	/// <summary>
	/// 이미지의 가로 픽셀 크기를 가져옵니다.
	/// </summary>
	float	GetWidth();
	/// <summary>
	/// 이미지의 가로 세로 크기를 가져옵니다.
	/// </summary>
	float	GetHeight();
	/// <summary>
	/// 게임 안에서의 가로 길이를 가져옵니다.
	/// </summary>
	float	GetCoordWidth();
	/// <summary>
	/// 게임 안에서의 세로 길이를 가져옵니다.
	/// </summary>
	float	GetCoordHeight();
	Sprite* GetSprite();
	glm::vec4 GetColor();


	bool HasAlpha();

private:
	/// <summary>
	/// 현재 matrix를 기반으로 Vertex위치를 계산, 적용시킵니다.
	/// </summary>
	void CalculateVertexPos();

private:
	Sprite* m_pSprite;
	GLuint* m_pShader;
	GLuint* m_pMVP;			// Model -> View -> Projection

	GLuint m_vertexID;
	GLuint m_uvID;
	GLuint m_MVP_MatrixID;
	GLuint m_myColorID;

	bool m_isUi;
	glm::vec4 m_color;
};

