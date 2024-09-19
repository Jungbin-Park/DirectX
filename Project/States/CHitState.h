#pragma once
#include <Engine/CState.h>

class CHitState :
    public CState
{
private:


public:
	virtual void Enter();
	virtual void FinalTick();
	virtual void Exit();

public:
	CLONE(CHitState);
	CHitState();
	~CHitState();
};

