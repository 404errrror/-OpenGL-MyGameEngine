#pragma once
#include "GameObject.h"
class ItemBlockTxtEffect :
	public GameObject
{
public:
	ItemBlockTxtEffect();
	~ItemBlockTxtEffect();

	virtual void Initialize();
	virtual void Start();
	virtual void Update();

	void SetSprite(const char* spriteKey);
private:
	Image* m_pImage;
	ColorAnimation* m_pColorAni;
};

