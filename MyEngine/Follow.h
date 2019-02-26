#pragma once
#include "Component.h"
#include "Global.h"
class Transform;

class Follow :
	public Component
{
public:
	static std::list<Follow*> list;
public:
	Follow(GameObject& gameObject);
	~Follow();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;

	void SetTarget(Transform* target);
	void SetFollowSpeed(float speed);
private:
	Transform* m_pTarget;
	float m_speed;
};

