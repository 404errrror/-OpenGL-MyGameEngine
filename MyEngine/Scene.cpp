#include "Scene.h"

std::list<Scene*> Scene::list;

Scene::Scene(const char* name)
{
	m_name = name;

	list.push_back(this);
}


Scene::~Scene()
{
}


void Scene::Initialize()
{

	for (std::list<Transform*>::iterator it = Transform::list.begin(); it != Transform::list.end(); ++it)
		(*it)->Initialize();

	for (std::list<GameObject*>::iterator it = GameObject::list.begin(); it != GameObject::list.end(); ++it)
		(*it)->Initialize();


}

void Scene::Update()
{
	for (std::list<GameObject*>::iterator it = GameObject::list.begin(); it != GameObject::list.end(); ++it)
		if ((*it)->m_active)
			(*it)->Update();

	for (std::list<Follow*>::iterator it = Follow::list.begin(); it != Follow::list.end(); ++it)
		if ((*it)->m_enable && (*it)->gameObject.m_active)
			(*it)->Update();

	for (std::list<BoxCollider*>::iterator it = BoxCollider::list.begin(); it != BoxCollider::list.end(); ++it)
		if ((*it)->m_enable && (*it)->gameObject.m_active)
			(*it)->Update();

	Physics2D::Update();		// 순서주의!! 꼭 Rigidbody2D 직전에 업뎃해야함. Transform 때문에.

	for (std::list<RigidBody2D*>::iterator it = RigidBody2D::list.begin(); it != RigidBody2D::list.end(); ++it)
		if ((*it)->m_enable && (*it)->gameObject.m_active)
			(*it)->Update();

	for (std::list<GameObject*>::iterator it = GameObject::list.begin(); it != GameObject::list.end(); ++it)
		if ((*it)->m_active && (*it)->m_remove == false)
			(*it)->UpdateCollision();

	for (std::list<CameraC*>::iterator it = CameraC::list.begin(); it != CameraC::list.end(); ++it)
		if ((*it)->m_enable && (*it)->gameObject.m_active)
			(*it)->Update();

	for (std::list<Animation*>::iterator it = Animation::list.begin(); it != Animation::list.end(); ++it)
		if ((*it)->m_enable && (*it)->gameObject.m_active)
			(*it)->Update();

	for (std::list<ShapeAnimation*>::iterator it = ShapeAnimation::list.begin(); it != ShapeAnimation::list.end(); ++it)
		if ((*it)->m_enable && (*it)->gameObject.m_active)
			(*it)->Update();

	for (std::list<ColorAnimation*>::iterator it = ColorAnimation::list.begin(); it != ColorAnimation::list.end(); ++it)
		if ((*it)->m_enable && (*it)->gameObject.m_active)
			(*it)->Update();

	for (std::list<Button*>::iterator it = Button::list.begin(); it != Button::list.end(); ++it)
		if ((*it)->m_enable && (*it)->gameObject.m_active)
			(*it)->Update();

	//glDisable(GL_BLEND);
	////glEnable(GL_DEPTH_TEST);
	//glDepthMask(GL_TRUE);
	// 불투명한 애들 먼저 그리고나서
	for (std::list<Image*>::iterator it = Image::list.begin(); it != Image::list.end(); ++it)
		if ((*it)->m_enable && (*it)->gameObject.m_active)
		{
			(*it)->Update();
		}

	
	for (std::list<Line*>::iterator it = Line::list.begin(); it != Line::list.end(); ++it)
		if ((*it)->m_enable && (*it)->gameObject.m_active)
			(*it)->Update();


	// RemoveCheck

	for (std::list<GameObject*>::iterator it = GameObject::list.begin(); it != GameObject::list.end(); )
	{
		if ((*it)->m_remove)
		{
			(*it)->Release();
			delete *it;

			it = GameObject::list.erase(it);
		}
		else
			++it;
	}

}

void Scene::Release()
{
	for (std::list<GameObject*>::iterator it = GameObject::list.begin(); it != GameObject::list.end();)
	{
		(*it)->m_remove = true;
		(*it)->Release();
		delete *it;
		it = GameObject::list.erase(it);
	}

	GameObject::list.clear();
	Follow::list.clear();
	BoxCollider::list.clear();
	RigidBody2D::list.clear();
	CameraC::list.clear();
	Animation::list.clear();
	ShapeAnimation::list.clear();
	ColorAnimation::list.clear();
	Button::list.clear();
	Image::list.clear();
	Line::list.clear();
}


void Scene::SetName(const char* name)
{
	m_name = name;
}


std::string Scene::GetName()
{
	return m_name;
}