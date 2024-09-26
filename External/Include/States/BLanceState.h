#pragma once
#include <Engine/CState.h>

class BLanceState :
    public CState
{
private:
	CGameObject*			m_Target;

	float					m_Timer;
	float					m_ShootTime;
	bool					m_bCountStart;
	bool					m_IsShoot;
	bool					m_ChangeState;

	vector<CGameObject*>    m_vecSpawnedLance;
	Ptr<CPrefab>            m_LancePref;
	float					m_LanceSpacing;
	int						m_LanceCount;

private:
	void InitLance();
	void ShootLance();

public:
	virtual void Enter();
	virtual void FinalTick();
	virtual void Exit();

public:
	CLONE(BLanceState);
	BLanceState();
	~BLanceState();
};

