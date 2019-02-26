#pragma once
#include "GameObject.h"
#include "Global.h"
class Bullet :
	public GameObject
{
public:
	static std::list<Bullet*> myList;
public:
	Bullet();
	~Bullet();

	void Initialize()	override;
	void Start()		override;
	void Update()		override;
	void Release()		override;

private:

};

