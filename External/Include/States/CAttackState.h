#pragma once
#include <Engine/CState.h>

class CAttackState :
    public CState
{
private:
	float	m_AttackRange;

	bool	m_bPlayRightAnim;
	bool	m_bPlayLeftAnim;

public:
	virtual void Enter();
	virtual void FinalTick();
	virtual void Exit();

public:
	CLONE(CAttackState);
	CAttackState();
	~CAttackState();
};

