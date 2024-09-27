#pragma once
#include <Engine/CState.h>

class PMoveState :
    public CState
{
private:
	float			m_Speed;

	eDIR				m_Direction;
	eDIR				m_CollisionDir;

public:
	virtual void Enter();
	virtual void FinalTick();
	virtual void Exit();

public:
	CLONE(PMoveState);
	PMoveState();
	~PMoveState();
};

