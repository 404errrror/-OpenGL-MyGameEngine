#include "InvenButton.h"



InvenButton::InvenButton(GameObject& gameObject) : Button(gameObject)
{
}


InvenButton::~InvenButton()
{
}


void InvenButton::Release()
{

}


void InvenButton::PointerEnter()
{
	Button::PointerEnter();
}


void InvenButton::PointerDown()
{
	Button::PointerEnter();

}