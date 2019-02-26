#pragma once
#include "Component.h"
#include "Global.h"
class Image;
class BoxCollider :
	public Component
{
public:
	static std::list<BoxCollider*> list;

public:
	BoxCollider(GameObject& gameObject);
	~BoxCollider();

	void Initialize() override;
	void Update() override;
	void Release() override;

	float GetWidth();
	float GetHeight();
	bool GetIgnoreRaycast();

	void SetWidth(float width);
	void SetHeight(float width);
	void SetIgnoreRaycast(bool ignoreRaycast);
	void SetOffset(glm::vec3 offset);
	/// <summary>
	/// 반발력을 설정합니다.
	/// </summary>
	void SetRestituion(float scale);

	// 충돌 코드들은 나중에 Collider의 상속을 받게한 뒤, override하기.
	/// <summary>
	/// 점과의 충돌을 검사합니다.
	/// </summary>
	bool CollisionCheck(glm::vec2 point);


private:
	float m_width;
	float m_height;
	bool m_ignoreRaycast;
	glm::vec3 m_offset;
	b2Body* m_pBody;
	b2FixtureDef m_fixtureDef;
	b2PolygonShape m_shape;


	// test
	GLuint m_vboIds[1];
	GLuint m_MVP_matrixID;
	GLuint m_colorId;
	b2Vec2 m_vertices[8];
};

