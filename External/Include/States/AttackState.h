#pragma once
#include <Engine/CState.h>

class AttackState :
    public CState
{
public:
	virtual void Enter();
	virtual void FinalTick();
	virtual void Exit();

public:
	AttackState();
	~AttackState();
};

