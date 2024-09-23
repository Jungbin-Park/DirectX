#pragma once
#include <Engine/CState.h>

class BIdleState :
    public CState
{
public:
	virtual void Enter();
	virtual void FinalTick();
	virtual void Exit();

public:
	CLONE(BIdleState);
	BIdleState();
	~BIdleState();
};

