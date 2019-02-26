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
	/// 모든 컴포넌트의 메모리를 해제합니다.
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
	/// direction 만큼 이동합니다. isWorld가 true라면 월드 좌표를 기준으로 이동합니다.
	/// </summary>
	void Translate(glm::vec3 direction, bool isWorld = false);
	/// <summary>
	/// 현재 각도를 기준으로 회전합니다.
	/// </summary>
	void Rotate(glm::vec3 eulerAngle);
	void Rotate(glm::vec3 eulerAngle, glm::vec3 pivot);
	void RotateRadian(glm::vec3 radian);
	void RotateRadian(glm::vec3 radian, glm::vec3 pivot);
	/// <summary>
	/// vector.up이 point를 바라보도록 회전합니다.
	/// </summary>
	void LookAt2D(glm::vec3 point);
	/// <summary>
	/// point1이 point2를 바라볼때의 Z축 회전값을 반환합니다.
	/// </summary>
	static float LookAt2D(glm::vec3 point1, glm::vec3 point2);
	/// <summary>
	/// point를 바라봅니다.
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