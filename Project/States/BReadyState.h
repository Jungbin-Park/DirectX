#pragma once
#include <Engine/CState.h>

class BReadyState :
    public CState
{
public:
	virtual void Enter();
	virtual void FinalTick();
	virtual void Exit();

public:
	CLONE(BReadyState);
	BReadyState();
	~BReadyState();
};

