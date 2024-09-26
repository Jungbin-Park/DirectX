#include "pch.h"
#include "BSlashState.h"

#include <Engine/CTransform.h>
#include <Engine/CGameObject.h>
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

#include <Scripts/CBSlashScript.h>

BSlashState::BSlashState()
	: CState(STATE_TYPE::BOSSSLASHSTATE)
	, m_Target(nullptr)
	, m_Timer(0.f)
	, m_bIsSlash(false)
	, m_SwordPref(nullptr)
	, m_bCountStart(true)
	, m_SlashTime(2.f)
	, m_SpawnedSword(nullptr)
	, m_ChangeState(false)
{
}	  

BSlashState::~BSlashState()
{
}

void BSlashState::Enter()
{
	// IceSword
	m_SwordPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\IceSword.pref");

	CGameObject* pTarget = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Player");
	if (pTarget != nullptr)
		m_Target = pTarget;

	m_bCountStart = true;

	IceSword();
}

void BSlashState::FinalTick()
{
	if (m_bCountStart)
	{
		m_Timer += DT;

		if (m_Timer >= m_SlashTime)
		{
			m_bCountStart = false;
			m_bIsSlash = true;
			m_Timer = 0.f;
		}
	}

	if (m_bIsSlash)
	{
		m_bIsSlash = false;
		GetOwner()->FlipBookComponent()->Reset();
		Slash();
	}

	if (m_ChangeState)
	{
		m_Timer += DT;

		if (m_Timer >= 2.f)
		{
			GetOwner()->FSM()->ChangeState(L"BIdleState");
		}
	}
}

void BSlashState::IceSword()
{
	GetOwner()->FlipBookComponent()->Play(14, 5, false);

	Vec3 vRot = GetOwner()->Transform()->GetRelativeRotation();
	Vec3 vPos = GetOwner()->Transform()->GetRelativePos();

	vPos.y += 100.f;

	if (vRot.y == 0.f)
	{
		m_SpawnedSword = InstantiateSkill(m_SwordPref, 6, vPos, L"IceSword");
	}
	else
	{
		m_SpawnedSword = InstantiateSkill(m_SwordPref, 6, vPos, L"IceSword");
	}
}

void BSlashState::Slash()
{
	GetOwner()->FlipBookComponent()->Play(15, 10, false);

	CBSlashScript* vScript = (CBSlashScript*)m_SpawnedSword->GetScriptByName(L"CBSlashScript");

	if (vScript != nullptr)
	{
		vScript->Slash();
	}

	m_ChangeState = true;
}

void BSlashState::Exit()
{
	GetOwner()->FlipBookComponent()->Reset();
	m_ChangeState = false;
	m_Timer = 0.f;
}


