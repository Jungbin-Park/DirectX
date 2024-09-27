#pragma once
#include <Engine/CState.h>

class PFireDragonState :
    public CState
{
public:
	virtual void Enter();
	virtual void FinalTick();
	virtual void Exit();

public:
	CLONE(PFireDragonState);
	PFireDragonState();
	~PFireDragonState();
};

