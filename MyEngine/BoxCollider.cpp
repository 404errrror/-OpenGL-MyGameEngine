#include "BoxCollider.h"
#include "GameObject.h"
#include "Image.h"
#include "DebugDraw.h"
#include "ShaderManager.h"
#include "CameraC.h"

#define BUFFER_OFFSET(x)  ((const void*) (x))

std::list<BoxCollider*> BoxCollider::list;
BoxCollider::BoxCollider(GameObject& gameObject) : Component(gameObject)
{
	list.push_back(this);

	m_offset = glm::vec3(0.0f);
	m_pBody = nullptr;
	m_width = 1.0f;
	m_height = 1.0f;
	m_ignoreRaycast = false;

	m_fixtureDef.density = 1.0f;
	m_fixtureDef.friction = 1.0f;
	m_fixtureDef.restitution = 0.1f;
}


BoxCollider::~BoxCollider()
{
}


void BoxCollider::Initialize()
{
	Component::Initialize();


	m_pBody = gameObject.GetPhysicsBody();

	if (m_pBody == nullptr)
	{
		b2BodyDef bodyDef;
		glm::vec3 position = gameObject.transform.GetPosition();
		bodyDef.position.Set(position.x, position.y);

		m_pBody = gameObject.SetPhysicsBody(Physics2D::CreateBody(bodyDef));
	}

	m_shape.SetAsBox(0.1f, 0.1f);
	m_fixtureDef.shape = &m_shape;
	m_pBody->CreateFixture(&m_fixtureDef);

//#ifdef _DEBUG
//	//g_debugDraw.DrawPolygon(m_shape.m_vertices, m_shape.m_count, b2Color(0.0f, 1.0f, 0.0f));
//
//	//// test
//
//	m_MVP_matrixID = glGetUniformLocation(*ShaderManager::GetShader("LineShader"), "myMatrix");
//	m_colorId = glGetUniformLocation(*ShaderManager::GetShader("LineShader"), "myColor");
//	glGenBuffers(1, m_vboIds);
//
//	glEnableVertexAttribArray(0);
//
//	// Vertex buffer
//	glBindBuffer(GL_ARRAY_BUFFER, m_vboIds[0]);
//	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
//	glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_DYNAMIC_DRAW);
//
//	glDisableVertexAttribArray(0);
//	//// Cleanup
//	//glBindBuffer(GL_ARRAY_BUFFER, 0);
//	//glBindVertexArray(0);
//#endif // DEBUG

}


void BoxCollider::Update()
{
	Component::Update();

//#ifdef _DEBUG
//
//	m_vertices[0] = m_shape.m_vertices[0];
//	m_vertices[1] = m_shape.m_vertices[1];
//	m_vertices[2] = m_shape.m_vertices[1];
//	m_vertices[3] = m_shape.m_vertices[2];
//	m_vertices[4] = m_shape.m_vertices[2];
//	m_vertices[5] = m_shape.m_vertices[3];
//	m_vertices[6] = m_shape.m_vertices[3];
//	m_vertices[7] = m_shape.m_vertices[0];
//
//	glUseProgram(*ShaderManager::GetShader("LineShader"));
//	glm::vec3 position = gameObject.transform.GetPosition();
//	b2Transform transform = b2Transform(
//		b2Vec2(position.x, position.y),
//		b2Rot(-gameObject.transform.GetRotationRadian().z)
//	);
//
//	for (int i = 0; i < 8; ++i)
//		m_vertices[i] = b2Mul(transform, m_vertices[i]);
//
//	//glBindBuffer(GL_ARRAY_BUFFER, m_vboIds[0]);
//	glm::mat4 resultMatrix = CameraC::main->GetPerspectiveVP();
//	glUniformMatrix4fv(m_MVP_matrixID, 1, GL_FALSE, &resultMatrix[0][0]);
//	glUniform4f(m_colorId, 0.0f, 1.0f, 0.0f, 1.0f);
//	glEnableVertexAttribArray(0);
//	glBindBuffer(GL_ARRAY_BUFFER, m_vboIds[0]);
//	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(m_vertices), m_vertices);
//	glVertexAttribPointer(
//		0,                  // 0번째 속성(attribute). 0 이 될 특별한 이유는 없지만, 쉐이더의 레이아웃(layout)와 반드시 맞추어야 합니다.
//		2,                  // 크기(size)
//		GL_FLOAT,           // 타입(type)
//		GL_FALSE,           // 정규화(normalized)?
//		0,                  // 다음 요소 까지 간격(stride)
//		(void*)0            // 배열 버퍼의 오프셋(offset; 옮기는 값)
//	);
//
//	glDrawArrays(GL_LINES, 0, 8);
//
//	glDisableVertexAttribArray(0);
//	//glBindBuffer(GL_ARRAY_BUFFER, 0);
//	//glBindVertexArray(0);
//	//glUseProgram(0);
//
//#endif // DEBUG
}


void BoxCollider::Release()
{
	Component::Release();

	for (std::list<BoxCollider*>::iterator it = list.begin(); it != list.end(); ++it)
	{
		if (*it == this)
		{
			list.erase(it);
			return;
		}

	}
}


float BoxCollider::GetWidth()
{
	return m_width;
}


float BoxCollider::GetHeight()
{
	return m_height;
}


bool BoxCollider::GetIgnoreRaycast()
{
	return m_ignoreRaycast;
}


void BoxCollider::SetWidth(float width)
{
	if (width == 0.0f)
		std::cout << "콜라이더의 크기를 0또는 음수로 주면 에러가 발생합니다!!" << std::endl;

	m_shape.SetAsBox(width * 0.5f, m_height * 0.5f);
	m_pBody->DestroyFixture(m_pBody->GetFixtureList());
	m_pBody->CreateFixture(&m_fixtureDef);
	// 삭제하고 다시 만드는 이유.
	// fixtureDef를 토대로 Fixture이 만들어지므로 기존의 Fixture을 삭제하고 수정된 fixtureDef로 다시 Fixture을 만들어줘야함.
	m_width = width;
}


void BoxCollider::SetHeight(float height)
{
	if (height == 0.0f)
		std::cout << "콜라이더의 크기를 0또는 음수로 주면 에러가 발생합니다!!" << std::endl;

	m_shape.SetAsBox(m_width * 0.5f, height * 0.5f);
	m_pBody->DestroyFixture(m_pBody->GetFixtureList());
	m_pBody->CreateFixture(&m_fixtureDef);

	m_height = height;
}


void BoxCollider::SetOffset(glm::vec3 offset)
{
	m_offset = offset;
}


void BoxCollider::SetRestituion(float scale)
{

}


bool BoxCollider::CollisionCheck(glm::vec2 point)
{
	if (m_enable == false)
		return false;

	float halfWidth = m_width * 0.5f;
	float halfHeight = m_height * 0.5f;
	glm::vec3 position = gameObject.transform.GetPosition() + m_offset;

	if (point.x >= position.x - halfWidth &&
		point.x <= position.x + halfWidth &&
		point.y >= position.y - halfHeight &&
		point.y <= position.y + halfHeight
		)
		return true;
	else
		return false;
}


void BoxCollider::SetIgnoreRaycast(bool ignoreRaycast)
{
	m_ignoreRaycast = ignoreRaycast;
}