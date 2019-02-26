#pragma once
#include "Block.h"
class SkinBlock :
	public Block
{
public:
	SkinBlock();
	~SkinBlock();

	virtual void Initialize() override;

	virtual void Hitted(float damage) override;
	void SetSkin(const char* spriteKey);
private:
	std::string m_spriteKey;
};

