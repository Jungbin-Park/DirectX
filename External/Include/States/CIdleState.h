#pragma once
#include <Engine/CState.h>

class CIdleState :
    public CState
{
private:
	float	m_DetectRange;


public:
	virtual void Enter();
	virtual void FinalTick();
	virtual void Exit();

public:
	CLONE(CIdleState);
	CIdleState();
	~CIdleState();
};

