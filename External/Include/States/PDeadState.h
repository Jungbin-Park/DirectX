#pragma once
#include <Engine/CState.h>

class PDeadState :
    public CState
{
public:
	virtual void Enter();
	virtual void FinalTick();
	virtual void Exit();

public:
	CLONE(PDeadState);
	PDeadState();
	~PDeadState();
};

