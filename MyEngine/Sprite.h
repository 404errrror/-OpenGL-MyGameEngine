#pragma once
#include"Global.h"
class Sprite
{
public:
	Sprite();
	~Sprite();

	GLuint imageId;
	unsigned int m_width, m_height;
	bool m_hasAlpha;
};

