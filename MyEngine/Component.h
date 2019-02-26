#pragma once
#include "Global.h"
class GameObject;
class Component
{
public:
	GameObject& gameObject;
	bool m_enable;
public:
	Component(GameObject& gameObject);
	~Component();

	virtual void Initialize();
	virtual void Update();
	virtual void Release();

	template<typename T>
	T* GetComponent();
	template<typename T>
	T* AddComponent();

private:
	//virtual const char* GetType() = 0;
};

template<typename T>
T* Component::GetComponent()
{

	for (std::list<T*>::iterator it = T::list.begin();it != T::list.end(); ++it)
	{
		if (&gameObject == &(*it)->gameObject)
		{
			return (*it);
		}
	}
	return nullptr;
	//return (void);
}

template<typename T>
T* Component::AddComponent()
{
	T* component = new T(gameObject);
	component->Initialize();
	gameObject.transform.myComponentList.push_back(component);
	return component;
}