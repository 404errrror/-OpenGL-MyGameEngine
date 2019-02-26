#pragma once
#include "Button.h"
class InvenButton :
	public Button
{
public:
	InvenButton(GameObject& gameObject);
	~InvenButton();

	virtual void Release() override;

	virtual void PointerEnter() override;
	virtual void PointerDown() override;
};

