#pragma once
#include "Global.h"
#include "Component.h"
class Transform :
	public Component
{
public:
	static std::list<Transform*> list;
	std::list<Component*> myComponentList;
	GameObject& gameObject;
public:
	Transform(GameObject& gameObject);
	~Transform();

	void Initialize		() override;
	void Update			() override;
	/// <summary>
	/// ��� ������Ʈ�� �޸𸮸� �����մϴ�.
	/// </summary>
	void Release		() override;


	void SetPosition	(glm::vec3 position);
	void SetPosition	(float x, float y);
	void SetPosition	(float x, float y, float z);
	void SetPositionZ	(float z);
	void SetRotation	(glm::vec3 eulerAngle);
	void SetRotationRadian (glm::vec3 radian);
	void SetScale		(glm::vec3 scale);
	void SetParent		(Transform& parent);

	void SetLocalPosition	(glm::vec3 position);
	void SetLocalPosition	(float x, float y);
	void SetLocalPosition	(float x, float y, float z);

	void AddChild		(Transform& child);
	void RemoveChild	(Transform& child);
	void RemoveAllChild ();
	void RemoveParent	();
	void SetParentNull	();


	glm::vec3	GetPosition();
	glm::vec3	GetRotation();
	glm::vec3	GetRotationRadian();
	glm::vec3	GetScale();
	glm::mat4	GetMatrix();
	glm::mat4	GetLocalMatrix();

	glm::vec3 GetLocalPosition();
	glm::vec3 GetLocalScale();
	glm::vec3 GetLocalRotation();
	Transform* GetParent();

	/// <summary>
	/// direction ��ŭ �̵��մϴ�. isWorld�� true��� ���� ��ǥ�� �������� �̵��մϴ�.
	/// </summary>
	void Translate(glm::vec3 direction, bool isWorld = false);
	/// <summary>
	/// ���� ������ �������� ȸ���մϴ�.
	/// </summary>
	void Rotate(glm::vec3 eulerAngle);
	void Rotate(glm::vec3 eulerAngle, glm::vec3 pivot);
	void RotateRadian(glm::vec3 radian);
	void RotateRadian(glm::vec3 radian, glm::vec3 pivot);
	/// <summary>
	/// vector.up�� point�� �ٶ󺸵��� ȸ���մϴ�.
	/// </summary>
	void LookAt2D(glm::vec3 point);
	/// <summary>
	/// point1�� point2�� �ٶ󺼶��� Z�� ȸ������ ��ȯ�մϴ�.
	/// </summary>
	static float LookAt2D(glm::vec3 point1, glm::vec3 point2);
	/// <summary>
	/// point�� �ٶ󺾴ϴ�.
	/// </summary>
	void LookAt(glm::vec3 point);

private:
	std::list<Transform*> m_pChildList;

	glm::mat4 m_matrix;
	glm::vec3 m_position;
	glm::vec3 m_eulerAngle;
	glm::vec3 m_scale;

	Transform* m_pParent;

private:

};