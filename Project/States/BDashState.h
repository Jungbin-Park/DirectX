#pragma once
#include <Engine/CState.h>

class BDashState :
    public CState
{
private:
	Vec3	 m_Dir;
	Vec3	 m_TargetPos;

public:
	virtual void Enter();
	virtual void FinalTick();
	virtual void Exit();

public:
	CLONE(BDashState);
	BDashState();
	~BDashState();
};

