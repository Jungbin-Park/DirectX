#pragma once
#include <Engine/CState.h>

class MoveState :
    public CState
{
public:
	virtual void Enter();
	virtual void FinalTick();
	virtual void Exit();

public:
	MoveState();
	~MoveState();
};

