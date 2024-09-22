#pragma once
#include <Engine/CState.h>

class CHitState :
    public CState
{
private:
	float	m_HitTime;
	float	m_AttackRange;

	float	m_KnockBackSpeed;
	float	m_KnockBackTime;
	float	m_KnockBackAge;

private:
	void KnockBack();

public:
	virtual void Enter();
	virtual void FinalTick();
	virtual void Exit();

public:
	CLONE(CHitState);
	CHitState();
	~CHitState();
};

