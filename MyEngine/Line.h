#pragma once
#include "Component.h"
#include "Global.h"
class Line :
	public Component
{
public:
	static std::list<Line*> list;
public:
	Line(GameObject& gameObject);
	~Line();

	void Initialize() override;
	void Update() override;
	void Release() override;

	void SetPoint(glm::vec2 point1, glm::vec2 point2);
	void SetColor(glm::vec4 color);
private:
	glm::vec4 m_color;

	GLuint* m_pShader;
	GLuint m_vertexID;
	GLuint m_MVP_matrixID;
	GLuint m_colorID;
	glm::vec2 m_vertices[2];
};

