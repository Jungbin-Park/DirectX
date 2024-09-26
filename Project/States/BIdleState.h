#pragma once
#include <Engine/CState.h>

class BIdleState :
    public CState
{
private:
	float	m_WaitTime;
	bool	m_bWaitStart;

	bool	m_bLance;
	bool	m_bWater;
	bool	m_bSword;

public:
	virtual void Enter();
	virtual void FinalTick();
	virtual void Exit();

public:
	CLONE(BIdleState);
	BIdleState();
	~BIdleState();
};

