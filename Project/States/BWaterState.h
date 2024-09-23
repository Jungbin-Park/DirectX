#pragma once
#include <Engine/CState.h>

class BWaterState :
    public CState
{
public:
	virtual void Enter();
	virtual void FinalTick();
	virtual void Exit();

public:
	CLONE(BWaterState);
	BWaterState();
	~BWaterState();
};

