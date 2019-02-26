#pragma once
#include "GameObject.h"
class Cursor :
	public GameObject
{
public:
	static Cursor* instance;
public:
	Cursor();
	~Cursor();

	virtual void Initialize();
	virtual void Start();
	virtual void Update();
	virtual void Release();

	void SetSprite(const char* spriteKey);
	void SetSprite(Sprite* spriteKey);

	void SetColor(glm::vec4 color);

private:
	Image* m_pImage;
};

