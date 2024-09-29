#include "pch.h"
#include "CAttackState.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CTransform.h>
#include <Engine/CTimeMgr.h>
#include <Engine/CAssetMgr.h>

CAttackState::CAttackState()
	: CState(STATE_TYPE::ATTACKSTATE)
	, m_AttackRange(100.f)
	, m_bPlayRightAnim(false)
	, m_bPlayLeftAnim(false)
	, m_AttackCoolDown(0.f)
	, m_AttackSound(nullptr)
{
}

CAttackState::~CAttackState()
{
}

void CAttackState::Enter()
{
	m_AttackSound = CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\GhoulAttack.wav");
	m_AttackSound->Play(1, 0.3f, true);

	m_AttackPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\MonHit.pref");

	m_bPlayLeftAnim = false;
	m_bPlayRightAnim = false;
	m_AttackCoolDown = 0.f;
}

void CAttackState::FinalTick()
{
	CGameObject* pPlayer = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Player");
	Vec3 vTargetPos = pPlayer->Transform()->GetRelativePos();
	Vec3 vPos = GetOwner()->Transform()->GetRelativePos();
	Vec3 vDir = vTargetPos - vPos;
	float Dist = sqrt(vDir.x * vDir.x + vDir.y * vDir.y);
	vDir.Normalize();

	// Animation
	if (vDir.x > 0)
	{
		m_bPlayLeftAnim = false;
		if (!m_bPlayRightAnim)
		{
			m_bPlayRightAnim = true;
			GetOwner()->FlipBookComponent()->Play(3, 5, false);

			// 공격 오브젝트 소환 오른쪽 방향

			InstantiateSkill(m_AttackPref, 6, vPos += vDir * 50.f, L"MonHit");
		}
	}
	else
	{
		m_bPlayRightAnim = false;
		if (!m_bPlayLeftAnim)
		{
			m_bPlayLeftAnim = true;
			GetOwner()->FlipBookComponent()->Play(2, 5, false);

			// 공격 오브젝트 소환 왼쪽 방향
			InstantiateSkill(m_AttackPref, 6, vPos += vDir * 50.f, L"MonHit");
		}
	}

	if (GetOwner()->FlipBookComponent()->IsFinish())
	{
		m_AttackCoolDown += DT;

		if(m_AttackCoolDown > 1.f)
			GetFSM()->ChangeState(L"IdleState");
	}
	
}

void CAttackState::Exit()
{
	GetOwner()->FlipBookComponent()->Reset();
	m_AttackSound->Stop();
}



