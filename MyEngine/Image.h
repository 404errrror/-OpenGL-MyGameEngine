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
	/// �̹����� �����մϴ�.
	/// </summary>
	bool		SetSprite(const char* imageKey);
	bool		SetSprite(Sprite* sprite);
	/// <summary>
	/// ���̴��� �����մϴ�
	/// </summary>
	bool		SetSahder(const char* shaderKey);

	/// <summary>
	/// false�� �����ϸ� ī�޶� ������ ���� �ʽ��ϴ�.
	/// </summary>
	void SetUI(bool isUi);
	/// <summary>
	/// ������ �����մϴ�. Unity�� color�� ���� ����� �մϴ�.
	/// </summary>
	void SetColor(glm::vec4 color);
	void SetColorAlpha(float alpha);

	/// <summary>
	/// �̹����� ���� �ȼ� ũ�⸦ �����ɴϴ�.
	/// </summary>
	float	GetWidth();
	/// <summary>
	/// �̹����� ���� ���� ũ�⸦ �����ɴϴ�.
	/// </summary>
	float	GetHeight();
	/// <summary>
	/// ���� �ȿ����� ���� ���̸� �����ɴϴ�.
	/// </summary>
	float	GetCoordWidth();
	/// <summary>
	/// ���� �ȿ����� ���� ���̸� �����ɴϴ�.
	/// </summary>
	float	GetCoordHeight();
	Sprite* GetSprite();
	glm::vec4 GetColor();


	bool HasAlpha();

private:
	/// <summary>
	/// ���� matrix�� ������� Vertex��ġ�� ���, �����ŵ�ϴ�.
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

