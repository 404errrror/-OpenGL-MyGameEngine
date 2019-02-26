#pragma once
#include "Block.h"
class ExplosionBlock :
	public Block
{
public:
	ExplosionBlock();
	~ExplosionBlock();

	virtual void Initialize() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void Release() override;
	virtual void Destory() override;
	virtual void DestoryEffect() override;

	virtual void OnCollisionEnter2D(std::list<BoxCollider*>& colliderList) override;
private:
	ShapeAnimation* m_pShapeAni;
	ColorAnimation* m_pColorAni;
	RigidBody2D* m_pRigid;
	bool m_isBreak;

	GameObject* m_pEffect;
	Image* m_pEffectImage;
	ShapeAnimation* m_pEffectShapeAni;
	ColorAnimation* m_pEffectColorAni;
};

