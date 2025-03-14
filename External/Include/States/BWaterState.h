#pragma once
#include <Engine/CState.h>

class BWaterState :
    public CState
{
private:
	CGameObject*			m_Target;

	float					m_Timer;
	bool					m_IsShoot;
	bool					m_bCountStart;
	bool					m_ChangeState;

	// Water
	vector<CGameObject*>    m_vecSpawnedWater;
	Ptr<CPrefab>            m_WaterPref;
	float                   m_WaterSpacing;
	int                     m_WaterCount;

	Ptr<CSound>				m_Sound1;


private:
	void InitWaterBall();
	void ShootWaterBall();

public:
	virtual void Enter();
	virtual void FinalTick();
	virtual void Exit();

public:
	CLONE(BWaterState);
	BWaterState();
	~BWaterState();
};

