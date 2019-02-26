#include "Transform.h"
#include "RigidBody2D.h"
#include "GameObject.h"

std::list<Transform*> Transform::list;

Transform::Transform(GameObject& gameObject) :Component(gameObject),gameObject(gameObject)
{
	list.push_back(this);
	m_pChildList.clear();
	m_matrix = glm::mat4(1.0f);
	m_pParent = nullptr;
}


Transform::~Transform()
{
}


void Transform::Initialize()
{
	m_matrix		= glm::mat4(1.0f);
	m_position		= glm::vec3(0.0f);
	m_eulerAngle	= glm::vec3(0.0f);
	m_scale			= glm::vec3(1.0f);
	m_pParent = nullptr;
}


void Transform::Update()
{	
}


void Transform::Release()
{
	// �ٸ� ������Ʈ���� �޸� ����.
	for (std::list<Component*>::iterator it = myComponentList.begin(); it != myComponentList.end();)
	{
		(*it)->Release();
		delete (*it);
		it = myComponentList.erase(it);
	}

	if (m_pParent != nullptr)					// �θ��� ������Ʈ�� ���� ������ ����.
		m_pParent->RemoveChild(*this);

	if(m_pChildList.size() != 0)			// ���� �ڽĿ�����Ʈ�� ������ ����.
		RemoveAllChild();


	for (std::list<Transform*>::iterator it = list.begin(); it != list.end(); ++it)
		if ((*it) == this)
		{
			list.erase(it);
			return;
		}

}


void Transform::SetPosition(glm::vec3 position)
{
	//for (std::list<Transform*>::iterator it = m_pChildList.begin(); it != m_pChildList.end(); ++it)
	//	(*it)->SetPosition((*it)->GetLocalPosition() + position);

	if (m_pParent != nullptr)
	{
		m_position = position - m_pParent->GetPosition();
	}
	else
	{
		m_position = position;
	}

	m_matrix[3].x = m_position.x;
	m_matrix[3].y = m_position.y;
	m_matrix[3].z = m_position.z;


	if (Physics2D::GetPhysicsWorld()->IsLocked() == false)			// ���������� ������Ʈ �Ǵµ��ȿ��� ���� ���õ� �Լ��� �޼������ �����Ű�� �ȵ�.
	{
		b2Body* body = gameObject.GetPhysicsBody();
		if (body != nullptr)
			body->SetTransform(b2Vec2(GetPosition().x, GetPosition().y), body->GetAngle());
	}
}


void Transform::SetPosition(float x, float y)
{
	//for (std::list<Transform*>::iterator it = m_pChildList.begin(); it != m_pChildList.end(); ++it)
	//	(*it)->SetPosition(
	//	(*it)->GetLocalPosition().x + x,
	//		(*it)->GetLocalPosition().y + y
	//	);

	if (m_pParent != nullptr)
	{
		m_position.x = x - m_pParent->GetPosition().x;
		m_position.y = y - m_pParent->GetPosition().y;
	}
	else
	{
		m_position.x = x;
		m_position.y = y;
	}
	m_matrix[3].x = m_position.x;
	m_matrix[3].y = m_position.y;


	b2Body* body = gameObject.GetPhysicsBody();
	if (body != nullptr)
		body->SetTransform(b2Vec2(m_position.x, m_position.y), body->GetAngle());
}


void Transform::SetPosition(float x, float y, float z)
{
	//for (std::list<Transform*>::iterator it = m_pChildList.begin(); it != m_pChildList.end(); ++it)
	//{
	//	glm::vec3 itPosition = (*it)->GetPosition();
	//	(*it)->SetPosition(itPosition.x + x, itPosition.y + y, itPosition.z + z);
	//}
	if (m_pParent != nullptr)
	{
		m_position.x = x - m_pParent->GetPosition().x;
		m_position.y = y - m_pParent->GetPosition().y;
		m_position.z= z - m_pParent->GetPosition().z;
	}
	else
	{
		m_position.x = x;
		m_position.y = y;
		m_position.z = z;
	}

	m_matrix[3].x = m_position.x;
	m_matrix[3].y = m_position.y;
	m_matrix[3].z = m_position.z;

	b2Body* body = gameObject.GetPhysicsBody();
	if (body != nullptr)
		body->SetTransform(b2Vec2(GetPosition().x, GetPosition().y), body->GetAngle());
}


void Transform::SetPositionZ(float z)
{


	if (m_pParent != nullptr)
	{
		m_matrix[3].z = 0;
		float parentY = m_pParent->GetRotation().y;
		if (parentY == 180.0f || parentY == -180.0f)				//  ���ؼ� �׳� ���ڵ�
		{
			m_matrix = glm::translate(glm::vec3(0, 0, -(z - m_pParent->GetPosition().z))) * m_matrix;
		}
		else
		{
			m_matrix = glm::translate(glm::vec3(0, 0, z - m_pParent->GetPosition().z)) * m_matrix;
		}
		m_position.z = m_matrix[3].z;
	}
	else
	{
		m_position.z = z;
		m_matrix[3].z = z;
	}

	//for (std::list<Transform*>::iterator it = m_pChildList.begin(); it != m_pChildList.end(); ++it)
	//	(*it)->SetPositionZ((*it)->GetPosition().z);
}


void Transform::SetRotation(glm::vec3 eulerAngle)
{

	Rotate(eulerAngle - m_eulerAngle);
	m_eulerAngle = eulerAngle;

	b2Body* body = gameObject.GetPhysicsBody();
	if (body != nullptr)
		body->SetTransform(
			b2Vec2(m_position.x, m_position.y), 
			m_eulerAngle.z * glm::pi<float>() / 180.0f);
}


void Transform::SetRotationRadian(glm::vec3 radianAngle)
{
	glm::vec3 eulerAngle = radianAngle * 180.0f / glm::pi<float>();
	RotateRadian(eulerAngle - m_eulerAngle);
	m_eulerAngle = eulerAngle;
}


void Transform::SetScale(glm::vec3 scale)
{
	//for (std::list<Transform*>::iterator it = m_pChildList.begin(); it != m_pChildList.end(); ++it)
	//	(*it)->SetScale((*it)->GetLocalScale() + scale);
	if (scale.x == 0.0f)
		scale.x = 0.00001f;
	if (scale.y == 0.0f)
		scale.y = 0.00001f;

	m_matrix = m_matrix * glm::scale(scale / m_scale) * glm::mat4(1);
	m_scale = scale;


}


void Transform::SetParent(Transform& parent)
{
	m_position = GetPosition();
	m_matrix = GetMatrix();
	if (m_pParent != nullptr)
	{
		m_pParent->RemoveChild(*this);
	}

	m_pParent = &parent;
	parent.AddChild(*this);

	// ����ȭ�ϱ�.
	glm::vec3 parentPos = parent.GetPosition();
	m_position -= parentPos;
	m_matrix[3].x -= parentPos.x;
	m_matrix[3].y -= parentPos.y;
	m_matrix[3].z -= parentPos.z;
}


void Transform::SetLocalPosition(glm::vec3 position)
{

	
	m_position = position;
	m_matrix[3].x = m_position.x;
	m_matrix[3].y = m_position.y;
	m_matrix[3].z = m_position.z;



	if (Physics2D::GetPhysicsWorld()->IsLocked() == false)			// ���������� ������Ʈ �Ǵµ��ȿ��� ���� ���õ� �Լ��� �޼������ �����Ű�� �ȵ�.
	{
		b2Body* body = gameObject.GetPhysicsBody();
		if (body != nullptr)
			body->SetTransform(b2Vec2(GetPosition().x, GetPosition().y), body->GetAngle());
	}
}


void Transform::SetLocalPosition(float x, float y)
{
	//if (m_pParent == nullptr)
	//{
	//	SetPosition(x,y);
	//	m_position.x = x;
	//	m_position.y = y;
	//}
	//else
	//{
	//	glm::vec3 parentPosition= m_pParent->GetPosition();
	//	SetPosition(x + parentPosition.x, y + parentPosition.y);
	//	m_position.x = x + parentPosition.x;
	//	m_position.y = y + parentPosition.y;
	//}

	m_position.x = x;
	m_position.y = y;
	m_matrix[3].x = x;
	m_matrix[3].y = y;



		b2Body* body = gameObject.GetPhysicsBody();
		if (body != nullptr)
			body->SetTransform(b2Vec2(GetPosition().x, GetPosition().y), body->GetAngle());
}


void Transform::SetLocalPosition(float x, float y, float z)
{
	if (m_pParent == nullptr)
	{
		SetPosition(x, y);
		m_position.x = x;
		m_position.y = y;
		m_position.z = z;
	}
	else
	{
		glm::vec3 parentPosition = m_pParent->GetPosition();
		SetPosition(x + parentPosition.x, y + parentPosition.y, z + parentPosition.z);
		m_position.x = x + parentPosition.x;
		m_position.y = y + parentPosition.y;
		m_position.y = z + parentPosition.z;
	}
}



glm::vec3 Transform::GetPosition()
{

	if (m_pParent != nullptr)
		return m_position + m_pParent->GetPosition();
	return m_position;
}


glm::vec3 Transform::GetRotation()
{
	if (m_pParent != nullptr)
		return m_eulerAngle - m_pParent->GetRotation();
	return m_eulerAngle;
}


glm::vec3 Transform::GetRotationRadian()
{
	return m_eulerAngle * glm::pi<float>() / 180.0f ;
}


glm::vec3 Transform::GetScale()
{
	return m_scale;
}


glm::vec3 Transform::GetLocalPosition()
{

	return m_position;
}


glm::vec3 Transform::GetLocalScale()
{
	if (m_pParent == nullptr)
		return m_scale;
	else
		return m_scale - m_pParent->GetScale();
}


glm::vec3 Transform::GetLocalRotation()
{
	//if (m_pParent == nullptr)
	//	return m_eulerAngle;
	//else
	return m_eulerAngle;
}


Transform* Transform::GetParent()
{
	return m_pParent;
}


void Transform::AddChild(Transform& child)
{
	m_pChildList.push_back(&child);
}


void Transform::RemoveChild(Transform& child)
{
	if (m_pChildList.empty())
		return;

	for(
		std::list<Transform*>::iterator it = m_pChildList.begin(); 
		it != m_pChildList.end(); ++it
		)
		if (*it == &child)
		{
			m_pChildList.erase(it);
			return;
		}
}


void Transform::RemoveAllChild()
{
	for (std::list<Transform*>::iterator it = m_pChildList.begin(); it != m_pChildList.end();)
	{
		(*it)->SetParentNull();
		it = m_pChildList.erase(it);
	}
}


void Transform::RemoveParent()
{

	m_matrix = GetMatrix();
	m_position = GetPosition();
	m_eulerAngle = GetRotation();
	m_scale = GetScale();

	if (m_pParent == nullptr)
		return;
	m_pParent->RemoveChild(*this);

	m_pParent = nullptr;


	b2Body* body = gameObject.GetPhysicsBody();
	if (body != nullptr)
		body->SetTransform(b2Vec2(GetPosition().x, GetPosition().y), body->GetAngle());
}


void Transform::SetParentNull()
{
	m_pParent = nullptr;
}


glm::mat4 Transform::GetMatrix()
{
	if (m_pParent != nullptr)
		return m_pParent->GetMatrix() * m_matrix;
	return m_matrix;
}


glm::mat4 Transform::GetLocalMatrix()
{
	return m_matrix;
}


void Transform::Translate(glm::vec3 direction, bool isWorld)
{
	glm::vec3 startPos = m_position;			// chlid�̵��� ����, �ð���� �ӽ÷�.
	glm::vec3 endPos;

	if (									// World ��ǥ�� �������� �̵�.
		isWorld == true ||
		m_eulerAngle == glm::vec3(0)		// ������ 0����� ������ ����,  Local�̳� World�� ���� ��ǥ�踦 ������ ����.
		)
	{
		m_matrix = glm::translate(direction) * m_matrix;
	}


	else									// Local ��ǥ�� �������� �̵�.
	{
		glm::vec3 position(m_matrix[3].x, m_matrix[3].y, m_matrix[3].z);
		glm::vec3 rotation = m_eulerAngle;
		glm::vec3 scale = m_scale;
		
		float rotScale = glm::distance(rotation, glm::vec3(0));
		
		m_matrix = glm::mat4(1.0f);
		m_matrix = glm::translate(direction) * glm::scale(scale) * m_matrix;
		m_matrix = glm::rotate(glm::radians(rotScale) * -1, glm::normalize(rotation)) * m_matrix;
		m_matrix = glm::translate(position) * m_matrix;
	}

	m_position = glm::vec3(m_matrix[3].x, m_matrix[3].y, m_matrix[3].z);
	endPos = m_position;

	// child
	//for (std::list<Transform*>::iterator it = m_pChildList.begin(); it != m_pChildList.end(); ++it)
	//	(*it)->Translate(endPos - startPos, true);

	// Rigidbody
	b2Body* body = gameObject.GetPhysicsBody();
	if (body != nullptr)
		body->SetTransform(b2Vec2(m_position.x, m_position.y), body->GetAngle());

}


void Transform::Rotate(glm::vec3 eulerAngle)
{

	//m_matrix = glm::rotate(1.0f,glm::radians(eulerAngle)) * m_matrix; // ���� �˾Ҵµ� �ȵǵ��.
	
	if (eulerAngle == glm::vec3(0))		// 0���� ȸ���ϸ� �������� ������.
		return;

	m_eulerAngle += eulerAngle;
	glm::vec3 position(m_matrix[3].x, m_matrix[3].y, m_matrix[3].z);
	glm::mat4 parentMatrix;

	//position = GetPosition();

	//if (m_pParent != nullptr)
	//{
	//	parentMatrix = GetMatrix();

	//	m_matrix[3].x = parentMatrix[3].x;
	//	m_matrix[3].y = parentMatrix[3].x;
	//	m_matrix[3].z = parentMatrix[3].x;

	//}
	//else
	//{
		m_matrix[3].x = 0;
		m_matrix[3].y = 0;
		m_matrix[3].z = 0;
	//}


	//m_matrix =	glm::rotate(glm::radians(eulerAngle.x), glm::vec3(-1, 0, 0)) *
	//			glm::rotate(glm::radians(eulerAngle.y), glm::vec3(0, -1, 0)) *
	//			glm::rotate(glm::radians(eulerAngle.z), glm::vec3(0, 0, -1)) * m_matrix;

	// �̰͵� ����ȭ�� ���� ���ʹϾ����� �ٲ���ҵ�
	float vecScale = glm::distance(eulerAngle,glm::vec3(0));
	//if (m_pParent != nullptr)
		//m_matrix = glm::rotate(glm::radians(vecScale) * -1, glm::normalize(eulerAngle)) * m_matrix;
	//else
		m_matrix = glm::rotate(glm::radians(vecScale) * -1, glm::normalize(eulerAngle)) * m_matrix;

	m_matrix[3].x = position.x;
	m_matrix[3].y = position.y;
	m_matrix[3].z = position.z;

	//// child
	//for (std::list<Transform*>::iterator it = m_pChildList.begin(); it != m_pChildList.end(); ++it)
	//	(*it)->Rotate(eulerAngle, GetPosition());
}


void Transform::Rotate(glm::vec3 eulerAngle, glm::vec3 pivot)
{
	if (eulerAngle == glm::vec3(0))		// 0���� ȸ���ϸ� �������� ������.
		return;
	
	m_eulerAngle += eulerAngle;
	glm::vec3 position(m_matrix[3].x, m_matrix[3].y, m_matrix[3].z);
	glm::vec3 movePosition(-pivot);

	// �θ� �������� �̵�. (�̷��� �����ϸ� ����)
	m_matrix[3].x = position.x - pivot.x;
	m_matrix[3].y = position.y - pivot.y;
	m_matrix[3].z = position.z - pivot.z;

	// ������ �������� ȸ��.
	float vecScale = glm::distance(eulerAngle, glm::vec3(0));
	m_matrix = glm::rotate(glm::radians(vecScale) * -1, glm::normalize(eulerAngle)) * m_matrix;

	// ��ġ ����
	m_matrix[3].x += pivot.x;
	m_matrix[3].y += pivot.y;
	m_matrix[3].z += pivot.z;

	m_position = glm::vec3(m_matrix[3].x, m_matrix[3].y, m_matrix[3].z);

	for (std::list<Transform*>::iterator it = m_pChildList.begin(); it != m_pChildList.end(); ++it)
		(*it)->Rotate(eulerAngle, pivot);
}


void Transform::RotateRadian(glm::vec3 radian)
{
	if (radian == glm::vec3(0))		// 0���� ȸ���ϸ� �������� ������.
		return;

	m_eulerAngle += radian * 180.0f / glm::pi<float>(); // ---> glm::euler<float>() �� ���غ���.
	glm::vec3 position(m_matrix[3].x, m_matrix[3].y, m_matrix[3].z);

	m_matrix[3].x = 0;
	m_matrix[3].y = 0;
	m_matrix[3].z = 0;


	// �̰͵� ����ȭ�� ���� ���ʹϾ����� �ٲ���ҵ�
	float vecScale = glm::distance(radian, glm::vec3(0));
	m_matrix = glm::rotate(vecScale * -1, glm::normalize(radian)) * m_matrix;

	m_matrix[3].x = position.x;
	m_matrix[3].y = position.y;
	m_matrix[3].z = position.z;

	// child
	for (std::list<Transform*>::iterator it = m_pChildList.begin(); it != m_pChildList.end(); ++it)
		(*it)->RotateRadian(radian, m_position);
}

void Transform::RotateRadian(glm::vec3 radian, glm::vec3 pivot)
{
	if (radian == glm::vec3(0))		// 0���� ȸ���ϸ� �������� ������.
		return;

	m_eulerAngle += radian * 180.0f / glm::pi<float>();
	glm::vec3 position(m_matrix[3].x, m_matrix[3].y, m_matrix[3].z);
	glm::vec3 movePosition(-pivot);

	// �θ� �������� �̵�. (�̷��� �����ϸ� ����)
	m_matrix[3].x = position.x - pivot.x;
	m_matrix[3].y = position.y - pivot.y;
	m_matrix[3].z = position.z - pivot.z;

	// ������ �������� ȸ��.
	float vecScale = glm::distance(radian, glm::vec3(0));
	m_matrix = glm::rotate(vecScale * -1, glm::normalize(radian)) * m_matrix;

	// ��ġ ����
	m_matrix[3].x += pivot.x;
	m_matrix[3].y += pivot.y;
	m_matrix[3].z += pivot.z;

	m_position = glm::vec3(m_matrix[3].x, m_matrix[3].y, m_matrix[3].z);
}


void Transform::LookAt2D(glm::vec3 point)
{
	glm::vec3 position = GetPosition();
	glm::vec2 vector = glm::vec2(point.x - position.x, point.y - position.y);
	//glm::vec2 vector = glm::vec2(point.x - m_position.x, point.y - m_position.y);

	float rotationZ = glm::atan(vector.y / vector.x);

	rotationZ *= 180.0f/glm::pi<float>();
	rotationZ = (rotationZ + 90) * -1 ;			// ������ ��ǥ�踦 ���ӳ��� ��ǥ��� �°� �ϱ� ���ؼ�.
	
	if (vector.x >= 0)							// ������ �𸣰����� �ٶ󺸴� ��ü�� ���ʿ� ������ 180�� �ݴ�������� �ٶ�.
		rotationZ += 180;
	// 180�� ������
	SetRotation(glm::vec3(m_eulerAngle.x, m_eulerAngle.y, rotationZ));
}



// ���� �̻���. ���߿� ��ġ��
float Transform::LookAt2D(glm::vec3 point1, glm::vec3 point2)
{
	glm::vec2 vector = glm::vec2(point2.x - point1.x, point2.y - point1.y);

	float rotationZ = glm::atan(vector.y / vector.x);

	rotationZ *= 180.0f / glm::pi<float>();
	rotationZ = (rotationZ + 90) * -1;			// ������ ��ǥ�踦 ���ӳ��� ��ǥ��� �°� �ϱ� ���ؼ�.

	if (vector.x >= 0)							// ������ �𸣰����� �ٶ󺸴� ��ü�� ���ʿ� ������ 180�� �ݴ�������� �ٶ�.
		rotationZ += 180;

	return rotationZ;
}

void Transform::LookAt(glm::vec3 point)
{
	m_matrix = glm::lookAt(m_position, point, glm::vec3(0, 1, 0));

}


