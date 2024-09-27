#pragma once
#include <Engine/CState.h>

class PSlashState :
    public CState
{
public:
	

private:
	float			m_Speed;
	Vec2			m_MouseDir;
	Vec3			m_MovedPos;

	eDIR				m_Direction;
	eDIR				m_CollisionDir;
	eDIR				m_AttackDir;

	float           m_AtkDashSpeed;
	float           m_AtkDashTime;
	float           m_AtkDashDuration;
	float           m_AttackFinishTime;
	Vec3            m_SlashPos;
	Vec3            m_SlashRot;

	int				m_KeyTapCount;
	int				m_ClickCount;

public:
	virtual void Enter();
	virtual void FinalTick();
	virtual void Exit();

public:
	CLONE(PSlashState);
	PSlashState();
	~PSlashState();
};

