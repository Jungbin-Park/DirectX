#pragma once
#include <Engine/CState.h>

class BWaterState :
    public CState
{
private:
	CGameObject*			m_Target;

	float					m_Timer;
	bool					m_IsShoot;

	// Water
	vector<CGameObject*>    m_vecSpawnedWater;
	Ptr<CPrefab>            m_WaterPref;
	float                   m_WaterSpacing;
	int                     m_WaterCount;


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

