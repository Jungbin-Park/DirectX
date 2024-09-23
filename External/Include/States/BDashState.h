#pragma once
#include <Engine/CState.h>

class BDashState :
    public CState
{
public:
	virtual void Enter();
	virtual void FinalTick();
	virtual void Exit();

public:
	CLONE(BDashState);
	BDashState();
	~BDashState();
};

