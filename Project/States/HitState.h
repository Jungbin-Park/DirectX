#pragma once
#include <Engine/CState.h>

class HitState :
    public CState
{
public:
	virtual void Enter();
	virtual void FinalTick();
	virtual void Exit();

public:
	HitState();
	~HitState();
};

