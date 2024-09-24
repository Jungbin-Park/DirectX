#pragma once
#include <Engine/CState.h>

class BLanceState :
    public CState
{
private:
	CGameObject*	m_Target;

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

