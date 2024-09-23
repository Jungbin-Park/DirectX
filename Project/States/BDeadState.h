#pragma once
#include <Engine/CState.h>

class BDeadState :
    public CState
{
public:
	virtual void Enter();
	virtual void FinalTick();
	virtual void Exit();

public:
	CLONE(BDeadState);
	BDeadState();
	~BDeadState();
};

