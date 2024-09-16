#pragma once
#include <Engine/CState.h>

class IdleState :
    public CState
{
private:


public:
	virtual void Enter();
	virtual void FinalTick();
	virtual void Exit();

public:
	IdleState();
	~IdleState();
};

