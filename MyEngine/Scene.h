#pragma once
#include "Global.h"
#include "CameraC.h"
#include "GameObject.h"
#include "Transform.h"
#include "Image.h"
#include "Animation.h"
#include "CameraC.h"
#include "RigidBody2D.h"
#include "BoxCollider.h"
#include "Button.h"
#include "Line.h"
#include "Follow.h"

class Scene
{
public:
	static std::list<Scene*> list;

public:
	Scene(const char* name);
	~Scene();

	virtual void Initialize();
	virtual void Update();
	virtual void Release();

	void SetName(const char* name);

	std::string GetName();

private:
	std::string m_name;
};

