#pragma once
#include <Engine/CState.h>

class PIdleState :
    public CState
{
private:

	eDIR				m_Direction;
	eDIR				m_CollisionDir;

public:
	eDIR GetDirection() { return m_Direction; }

	void SetDirection(eDIR _dir) { m_Direction = _dir; }

public:
	virtual void Enter();
	virtual void FinalTick();
	virtual void Exit();

public:
	CLONE(PIdleState);
	PIdleState();
	~PIdleState();
};

