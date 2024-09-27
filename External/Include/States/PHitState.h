#pragma once
#include <Engine/CState.h>

class PHitState :
    public CState
{
public:
	float	m_HitTime;

	float	m_KnockBackSpeed;
	float	m_KnockBackTime;
	float	m_KnockBackAge;

public:
	void KnockBack();

public:
	virtual void Enter();
	virtual void FinalTick();
	virtual void Exit();

public:
	CLONE(PHitState);
	PHitState();
	~PHitState();
};

