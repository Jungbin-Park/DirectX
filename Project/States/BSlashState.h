#pragma once
#include <Engine/CState.h>

class BSlashState
	: public CState
{
private:
	CGameObject*	m_Target;
	CGameObject*	m_SpawnedSword;

	float			m_Timer;
	float			m_SlashTime;

	bool			m_bIsSlash;
	bool			m_bCountStart;
	bool			m_ChangeState;

	Ptr<CPrefab>	m_SwordPref;

private:
	void IceSword();
	void Slash();


public:
	virtual void Enter();
	virtual void FinalTick();
	virtual void Exit();

public:
	CLONE(BSlashState);
	BSlashState();
	~BSlashState();
};

