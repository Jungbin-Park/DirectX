#pragma once
#include <Engine/CState.h>

class BSpawnState :
    public CState
{
private:
	

public:
	virtual void Enter();
	virtual void FinalTick();
	virtual void Exit();

public:
	CLONE(BSpawnState);
	BSpawnState();
	~BSpawnState();
};

