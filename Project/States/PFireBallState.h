#pragma once
#include <Engine/CState.h>

class PFireBallState :
    public CState
{
public:
	virtual void Enter();
	virtual void FinalTick();
	virtual void Exit();

public:
	CLONE(PFireBallState);
	PFireBallState();
	~PFireBallState();
};

