#pragma once
#include <Engine/CState.h>

class CHitState :
    public CState
{
private:
	float	m_HitTime;

public:
	virtual void Enter();
	virtual void FinalTick();
	virtual void Exit();

public:
	CLONE(CHitState);
	CHitState();
	~CHitState();
};

