#pragma once
#include "GameObject.h"
class CameraTarget :
	public GameObject
{
public:
	static CameraTarget* instance;
public:
	CameraTarget();
	~CameraTarget();

	virtual void Initialize() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void Release() override;

};

