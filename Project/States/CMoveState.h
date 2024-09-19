#pragma once
#include <Engine/CState.h>

class CMoveState :
    public CState
{
private:


public:
	virtual void Enter();
	virtual void FinalTick();
	virtual void Exit();

public:
	CLONE(CMoveState);
	CMoveState();
	~CMoveState();
};

