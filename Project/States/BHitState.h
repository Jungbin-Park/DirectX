#pragma once
#include <Engine/CState.h>

class BHitState :
    public CState
{
private:
	Ptr<CSound> m_HitSound;

	float	m_HitTime;

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
	CLONE(BHitState);
	BHitState();
	~BHitState();
};

