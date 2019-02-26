#pragma once
#include "Component.h"
#include "Global.h"

class CameraC :
	public Component
{
public:
	static CameraC* main;
	static std::list<CameraC*> list;
public:
	enum ViewType
	{
		Perspective, Ortho
	};

	CameraC(GameObject& gameObject);
	~CameraC();

	virtual void Initialize();
	virtual void Update();
	virtual void Release();

	void SetFov(float viewAngle);
	void SetMinRender(float minRender);
	void SetMaxRender(float maxRender);
	void SetViewType(ViewType viewType);

	/// <summary>
	/// View * PerspectiveProjection 을 반환합니다.
	/// </summary>
	glm::mat4 GetPerspectiveVP();
	/// <summary>
	/// View * OrthoProjection 을 반환합니다.
	/// </summary>
	glm::mat4 GetOrthoVP();
	glm::mat4 GetOrthoProjection();

private:
	void UpdatePersipective();

	float m_fov;
	float m_minRender;
	float m_maxRender;
	ViewType m_viewType;
	glm::mat4 m_perspectiveP;
	glm::mat4 m_orthoP;
};

