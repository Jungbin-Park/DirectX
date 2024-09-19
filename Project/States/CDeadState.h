#pragma once
#include <Engine/CState.h>

class CDeadState :
    public CState
{
private:


public:
	virtual void Enter();
	virtual void FinalTick();
	virtual void Exit();

public:
	CLONE(CDeadState);
	CDeadState();
	~CDeadState();
};

