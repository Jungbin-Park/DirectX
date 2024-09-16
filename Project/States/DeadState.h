#pragma once
#include <Engine/CState.h>

class DeadState :
    public CState
{
public:
	virtual void Enter();
	virtual void FinalTick();
	virtual void Exit();

public:
	DeadState();
	~DeadState();
};

