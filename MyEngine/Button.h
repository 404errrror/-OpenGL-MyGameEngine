#pragma once
#include "Component.h"
#include "Global.h"
#include <functional>
class Image;
class Sprite;
class Button :
	public Component
{
public:
	static std::list<Button*> list;
	enum State
	{
		None, Enter, Pressing, RightPressing, Up, RightUp
	};
public:
	Button(GameObject& gameObject);
	~Button();

	virtual void Initialize()	override;
	virtual void Update()		override;
	virtual void Release()		override;

	virtual void PointerEnter();
	virtual void PointerExit();
	virtual void PointerDown();
	virtual void PointerRightDown();
	virtual void PointerUp();
	virtual void PointerRightUp();
	virtual void  PointerOnClick();
	virtual void  PointerOnRightClick();

	void SetSprite(const char* imagekey);
	void SetFocusSprite(const char* imageKey);
	void SetDownSprite(const char* imageKey);


	void SetFunctionPointerEnter		(std::function<void(void)> fp);
	void SetFunctionPointerExit			(std::function<void(void)> fp);
	void SetFunctionPointerDown			(std::function<void(void)> fp);
	void SetFunctionPointerRightDown	(std::function<void(void)> fp);
	void SetFunctionPointerUp			(std::function<void(void)> fp);
	void SetFunctionPointerRightUp		(std::function<void(void)> fp);
	void SetFunctionOnClick				(std::function<void(void)> fp);
	void SetFunctionOnRightClick		(std::function<void(void)> fp);
private:
	Image* m_pImage;
	Sprite* m_pSprite;
	Sprite* m_pFocusSprite;
	Sprite* m_pDownSprite;

	float m_width;
	float m_height;

	State m_state;

	std::function<void(void)> fp_pointerEnter;
	std::function<void(void)> fp_pointerExit;
	std::function<void(void)> fp_pointerDown;
	std::function<void(void)> fp_pointerRightDown;
	std::function<void(void)> fp_pointerUp;
	std::function<void(void)> fp_pointerRightUp;
	std::function<void(void)> fp_onClick;
	std::function<void(void)> fp_onRightClick;

private:
	void UpdateSprite();
};

