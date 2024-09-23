#pragma once
#include <Engine/CState.h>

class BLanceState :
    public CState
{
public:
	virtual void Enter();
	virtual void FinalTick();
	virtual void Exit();

public:
	CLONE(BLanceState);
	BLanceState();
	~BLanceState();
};

