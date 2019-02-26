#include "Line.h"
#include "ShaderManager.h"
#include "CameraC.h"

std::list<Line*> Line::list;

Line::Line(GameObject& gameObject) : Component(gameObject)
{
	list.push_back(this);
	m_color = glm::vec4(1.0f);
}


Line::~Line()
{
}


void Line::Initialize()
{
	m_pShader = ShaderManager::GetShader("LineShader");
	m_MVP_matrixID = glGetUniformLocation(*m_pShader, "myMatrix");
	m_colorID = glGetUniformLocation(*m_pShader, "myColor");

	glGenBuffers(1, &m_vertexID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexID);	
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_DYNAMIC_DRAW);
}


void Line::Update()
{
	glm::mat4 resultMatrix = CameraC::main->GetPerspectiveVP();
	glUseProgram(*m_pShader);
	glUniformMatrix4fv(m_MVP_matrixID, 1, GL_FALSE, &resultMatrix[0][0]);
	glUniform4f(m_colorID, m_color.r, m_color.g, m_color.b, m_color.a);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexID);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(m_vertices), m_vertices);
	glVertexAttribPointer(
		0,                  // 0��° �Ӽ�(attribute). 0 �� �� Ư���� ������ ������, ���̴��� ���̾ƿ�(layout)�� �ݵ�� ���߾�� �մϴ�.
		2,                  // ũ��(size)
		GL_FLOAT,           // Ÿ��(type)
		GL_FALSE,           // ����ȭ(normalized)?
		0,                  // ���� ��� ���� ����(stride)
		(void*)0            // �迭 ������ ������(offset; �ű�� ��)
	);

	glDrawArrays(GL_LINES, 0, 2);

	glDisableVertexAttribArray(0);
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(MouseManager::GetPositionX(), MouseManager::GetPositionY());
	glEnd();
}


void Line::Release()
{
	for (std::list<Line*>::iterator it = list.begin(); it != list.end(); ++it)
	{
		if (*it == this)
		{
			list.erase(it);
			break;
		}
	}
	glDeleteBuffers(1, &m_vertexID);
}


void Line::SetPoint(glm::vec2 point1, glm::vec2 point2)
{
	m_vertices[0] = point1;
	m_vertices[1] = point2;
}


void Line::SetColor(glm::vec4 color)
{
	m_color = color;
}
