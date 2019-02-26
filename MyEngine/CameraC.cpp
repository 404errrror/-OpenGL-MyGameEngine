#include "CameraC.h"
#include "GameObject.h"

CameraC* CameraC::main = nullptr;
std::list<CameraC*> CameraC::list;

CameraC::CameraC(GameObject& gameObject) : Component(gameObject)
{
	if (main == nullptr)
		main = this;
	list.push_back(this);

	m_fov = glm::radians(70.0f);
	m_minRender = 0.1f;
	m_maxRender = 100.0f;
	m_viewType = ViewType::Perspective;

	UpdatePersipective();
	m_orthoP = glm::ortho(
		-g_coordWidth * 0.5f,
		g_coordWidth * 0.5f,
		-g_coordHeight * 0.5f, g_coordHeight * 0.5f,
		0.0f, 100.0f
	);
}


CameraC::~CameraC()
{
}


void CameraC::Initialize()
{
	Component::Initialize();
}


void CameraC::Update()
{
	Component::Update();

}


void CameraC::Release()
{
	Component::Release();
	if (CameraC::main == this)
		CameraC::main = nullptr;
	for (std::list<CameraC*>::iterator it = list.begin(); it != list.end(); ++it)
	{
		if (*it == this)
		{
			list.erase(it);
			return;
		}
	}
}


void CameraC::SetFov(float viewAngle)
{
	m_fov = viewAngle;
	UpdatePersipective();
}


void CameraC::SetMinRender(float minRender)
{
	m_minRender = minRender;
	UpdatePersipective();
}


void CameraC::SetMaxRender(float maxRender)
{
	m_maxRender = maxRender;
	UpdatePersipective();
}


void CameraC::SetViewType(ViewType viewType)
{
	m_viewType = viewType;
	UpdatePersipective();
}

/// <summary>
/// 원근 행렬을 반환합니다. 하지만 ViewType이 Ortho로 되있으면 직교 행렬을 반환합니다.
/// </summary>
glm::mat4 CameraC::GetPerspectiveVP()
{
	if (m_viewType == Perspective)
		return m_perspectiveP * gameObject.transform.GetMatrix();
	else
		return m_orthoP * gameObject.transform.GetMatrix();
}


glm::mat4 CameraC::GetOrthoVP()
{
	return m_orthoP * gameObject.transform.GetMatrix();
}


glm::mat4 CameraC::GetOrthoProjection()
{
	return m_orthoP * gameObject.transform.GetMatrix();
}


void CameraC::UpdatePersipective()
{
	m_perspectiveP = glm::perspective(
		m_fov,
		(float)g_width / (float)g_height,
		m_minRender,
		m_maxRender
	);
}