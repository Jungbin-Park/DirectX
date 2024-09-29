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
	, m_SlashTime(1.f)
	, m_SpawnedSword(nullptr)
	, m_ChangeState(false)
	, m_Sound1(nullptr)
	, m_Sound2(nullptr)
{
}	  

BSlashState::~BSlashState()
{
}

void BSlashState::Enter()
{
	m_Sound1 = CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\IceDaggerBasic.wav");
	m_Sound2 = CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\IceSwordInit.wav");
	m_Sound1->Play(1, 0.3f, false);
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
	GetOwner()->FlipBookComponent()->Play(14, 10, false);

	Vec3 vRot = GetOwner()->Transform()->GetRelativeRotation();
	Vec3 vPos = GetOwner()->Transform()->GetRelativePos();

	vPos.y += 100.f;

	m_SpawnedSword = InstantiateSkill(m_SwordPref, 6, vPos, L"IceSword");
}

void BSlashState::Slash()
{
	m_Sound2->Play(1, 0.3f, false);
	GetOwner()->FlipBookComponent()->Play(15, 10, false);

	CBSlashScript* vScript = nullptr;
	vScript = (CBSlashScript*)m_SpawnedSword->GetScriptByName(L"CBSlashScript");

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

	m_Sound1->Stop();
	m_Sound2->Stop();
}


