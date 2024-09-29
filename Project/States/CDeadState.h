#pragma once
#include <Engine/CState.h>

class CDeadState :
    public CState
{
private:
	Ptr<CSound>	m_DeadSound;

public:
	virtual void Enter();
	virtual void FinalTick();
	virtual void Exit();

public:
	CLONE(CDeadState);
	CDeadState();
	~CDeadState();
};

