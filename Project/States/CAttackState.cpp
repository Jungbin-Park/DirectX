#include "pch.h"
#include "CAttackState.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CTransform.h>
#include <Engine/CTimeMgr.h>

CAttackState::CAttackState()
	: CState(STATE_TYPE::ATTACKSTATE)
	, m_AttackRange(100.f)
	, m_bPlayRightAnim(false)
	, m_bPlayLeftAnim(false)
{
}

CAttackState::~CAttackState()
{
}

void CAttackState::Enter()
{
	m_bPlayLeftAnim = false;
	m_bPlayRightAnim = false;
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
		}
	}

	// ChangeState
	if (Dist > m_AttackRange)
		GetFSM()->ChangeState(L"MoveState");
}

void CAttackState::Exit()
{
}



