#pragma once
#include <Engine/CState.h>

class BSlashState
	: public CState
{
public:
	virtual void Enter();
	virtual void FinalTick();
	virtual void Exit();

public:
	CLONE(BSlashState);
	BSlashState();
	~BSlashState();
};

