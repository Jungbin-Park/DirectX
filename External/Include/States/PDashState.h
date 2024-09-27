#pragma once
#include <Engine/CState.h>

class PDashState :
    public CState
{
private:
	float					m_Speed;

	eDIR						m_Direction;
	eDIR						m_CollisionDir;

	float                   m_DashSpeed;
	float                   m_DashTime;
	float                   m_DashDuration;

	int						m_KeyTapCount;

public:
	virtual void Enter();
	virtual void FinalTick();
	virtual void Exit();

public:
	CLONE(PDashState);
	PDashState();
	~PDashState();
};

