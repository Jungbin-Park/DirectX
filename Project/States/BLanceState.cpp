#include "pch.h"
#include "BLanceState.h"

#include <Engine/CTransform.h>
#include <Engine/CGameObject.h>
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CAssetMgr.h>

#include <Scripts/CLanceScript.h>

BLanceState::BLanceState()
	: CState(STATE_TYPE::BOSSLANCESTATE)
	, m_vecSpawnedLance{}
	, m_LancePref(nullptr)
	, m_LanceSpacing(100.f)
	, m_LanceCount(3)
	, m_Timer(0.f)
	, m_IsShoot(false)
	, m_ShootTime(2.f)
	, m_bCountStart(true)
	, m_ChangeState(false)
{
}

BLanceState::~BLanceState()
{
}

void BLanceState::Enter()
{
	// Lance
	m_LancePref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\IceLance.pref");

	CGameObject* pTarget = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Player");
	if (pTarget != nullptr)
		m_Target = pTarget;

	m_bCountStart = true;

	InitLance();
}

void BLanceState::FinalTick()
{
	if (m_bCountStart)
	{
		m_Timer += DT;

		if (m_Timer >= m_ShootTime)
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
		ShootLance();
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

void BLanceState::InitLance()
{
	GetOwner()->FlipBookComponent()->Play(8, 5, false);
	//GetOwner()->FlipBookComponent()->Play(10, 5, false);
	//GetOwner()->FlipBookComponent()->Play(12, 5, false);

	m_vecSpawnedLance.clear();
	Vec3 vPos = GetOwner()->Transform()->GetRelativePos();

	float angle = 0.f;
	float xPos = vPos.x - 100.f;
	float yPos = vPos.y;

	for (int i = 0; i < m_LanceCount; i++)
	{
		CGameObject* pLance = InstantiateSkill(m_LancePref, 2, Vec3(xPos, yPos, 100.f), L"IceLance");
		m_vecSpawnedLance.push_back(pLance);
		xPos += 100.f;
	}
}

void BLanceState::ShootLance()
{
	GetOwner()->FlipBookComponent()->Play(9, 5, false);
	//GetOwner()->FlipBookComponent()->Play(11, 5, false);
	//GetOwner()->FlipBookComponent()->Play(13, 5, false);

	if (!m_vecSpawnedLance.empty())
	{
		//vector<CGameObject*>::iterator iter = m_vecSpawnedLance.begin();
		vector<CGameObject*>::reverse_iterator iter = m_vecSpawnedLance.rbegin();

		for (; iter != m_vecSpawnedLance.rend(); ++iter)
		{
			if ((*iter) == nullptr)
				continue;

			if((*iter)->GetScripts().empty())
				continue;

			CLanceScript* vScript = nullptr;
			vScript = (CLanceScript*)(*iter)->GetScriptByName(L"CLanceScript");

			if (vScript != nullptr)
			{
				vScript->ShootLance();
			}
		}
	}

	m_ChangeState = true;
}

void BLanceState::Exit()
{
	GetOwner()->FlipBookComponent()->Reset();

	m_ChangeState = false;
	m_Timer = 0.f;
}


