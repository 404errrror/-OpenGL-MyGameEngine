#pragma once
#include "Block.h"
class LaserBlock :
	public Block
{
public:
	LaserBlock();
	~LaserBlock();

	virtual void Initialize() override;
	virtual void Start() override;
	virtual void Update() override;
	
	void SetLaserCount(int num);

private:
	int m_laserCount;
	Line* m_pLine;
	Line* m_pLine2;

private:
	void LaserUpdate1();
	void LaserUpdate2();
	void LaserUpdate4();
};

