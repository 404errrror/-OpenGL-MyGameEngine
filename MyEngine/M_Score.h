#pragma once
#include "GameObject.h"
#include "GalagaNumber.h"
class M_Score :
	public GameObject
{
public:
	static M_Score* instance;
public:
	M_Score();
	~M_Score();

	virtual void Initialize();
	virtual void Start();
	virtual void Update();
	virtual void Release();

	int GetScore();
private:
	GalagaNumber* m_pScore;
};

