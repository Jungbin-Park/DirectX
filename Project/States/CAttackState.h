#pragma once
#include <Engine/CState.h>

class CAttackState :
    public CState
{
private:


public:
	virtual void Enter();
	virtual void FinalTick();
	virtual void Exit();

public:
	CLONE(CAttackState);
	CAttackState();
	~CAttackState();
};

