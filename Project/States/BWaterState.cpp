#include "pch.h"
#include "BWaterState.h"

#include <Engine/CTransform.h>
#include <Engine/CGameObject.h>
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

#include <Scripts/CWaterScript.h>


BWaterState::BWaterState()
	: CState(STATE_TYPE::BOSSWATERSTATE)
	, m_vecSpawnedWater{}
	, m_WaterPref(nullptr)
	, m_WaterCount(8)
	, m_WaterSpacing(100.f)
	, m_Timer(0.f)
	, m_IsShoot(false)
	, m_bCountStart(true)
	, m_ChangeState(false)
{
}

BWaterState::~BWaterState()
{
}



void BWaterState::Enter()
{
	// WaterBall
	m_WaterPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\WaterBall.pref");

	CGameObject* pTarget = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Player");
	if (pTarget != nullptr)
		m_Target = pTarget;

	m_bCountStart = true;

	InitWaterBall();
}

void BWaterState::FinalTick()
{
	if (m_bCountStart)
	{
		m_Timer += DT;

		if (m_Timer >= 2.f)
		{
			m_bCountStart = false;
			m_IsShoot = true;
			m_Timer = 0.f;
		}
	}

	if (m_IsShoot)
	{
		m_IsShoot = false;
		GetOwner()->FlipBookComponent()->Reset();
		ShootWaterBall();
	}

	if (m_ChangeState)
	{
		m_Timer += DT;

		if (m_Timer >= 3.f)
		{
			GetOwner()->FSM()->ChangeState(L"BIdleState");
		}
	}
}



void BWaterState::InitWaterBall()
{
	GetOwner()->FlipBookComponent()->Play(16, 5, false);

	m_vecSpawnedWater.clear();
	Vec3 vPos = GetOwner()->Transform()->GetRelativePos();

	float angle = 0.f;
	float xPos;
	float yPos;

	for (int i = 0; i < m_WaterCount; i++)
	{
		xPos = vPos.x + (cos(angle) * m_WaterSpacing);
		yPos = vPos.y + (sin(angle) * m_WaterSpacing);
		CGameObject* pWaterBall = InstantiateSkill(m_WaterPref, 6, Vec3(xPos, yPos, 100.f), L"WaterBall");
		m_vecSpawnedWater.push_back(pWaterBall);
		angle += (XM_2PI / (float)m_WaterCount);
	}


}

void BWaterState::ShootWaterBall()
{
	GetOwner()->FlipBookComponent()->Play(17, 10, false);

	if (!m_vecSpawnedWater.empty())
	{
		//vector<CGameObject*>::iterator iter = m_vecSpawnedWater.begin();
		vector<CGameObject*>::reverse_iterator iter = m_vecSpawnedWater.rbegin();

		float shootTime = 0.5f;

		for (; iter != m_vecSpawnedWater.rend(); ++iter)
		{
			if ((*iter) == nullptr)
				continue;

			CWaterScript* vScript = (CWaterScript*)(*iter)->GetScriptByName(L"CWaterScript");

			if (vScript != nullptr)
			{
				vScript->SetShootTime(shootTime);
			}

			shootTime += 0.3f;
		}
	}

	m_ChangeState = true;
}


void BWaterState::Exit()
{
	GetOwner()->FlipBookComponent()->Reset();

	m_ChangeState = false;
	m_Timer = 0.f;
}