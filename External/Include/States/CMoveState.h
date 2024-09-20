#pragma once
#include <Engine/CState.h>

class CMoveState :
    public CState
{
private:
	float	m_Speed;
	bool	m_bPlayRightAnim;
	bool	m_bPlayLeftAnim;

	float	m_AttackRange;

public:
	virtual void Enter();
	virtual void FinalTick();
	virtual void Exit();

public:
	CLONE(CMoveState);
	CMoveState();
	~CMoveState();
};

