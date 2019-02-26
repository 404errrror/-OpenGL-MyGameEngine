#include "Component.h"
#include "GameObject.h"


Component::Component(GameObject& gameObject):gameObject(gameObject)
{
	m_enable = true;
}


Component::~Component()
{
}


void Component::Initialize()
{
	m_enable = true;
}

void Component::Update()
{

}

void Component::Release()
{

}