#pragma once
#include <Engine/CState.h>

class CAttackState :
    public CState
{
private:
	Ptr<CPrefab>	m_AttackPref;
	Ptr<CSound>     m_AttackSound;

private:
	float	m_AttackRange;

	bool	m_bPlayRightAnim;
	bool	m_bPlayLeftAnim;

	float	m_AttackCoolDown;


public:
	virtual void Enter();
	virtual void FinalTick();
	virtual void Exit();

public:
	CLONE(CAttackState);
	CAttackState();
	~CAttackState();
};

