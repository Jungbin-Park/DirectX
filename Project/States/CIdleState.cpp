#include "pch.h"
#include "CIdleState.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CTransform.h>

CIdleState::CIdleState()
	: CState(STATE_TYPE::IDLESTATE)
	, m_DetectRange(300.f)
	, m_AttackRange(100.f)
{
}

CIdleState::~CIdleState()
{
}

void CIdleState::Enter()
{
	GetOwner()->FlipBookComponent()->Play(0, 10, false);
}

void CIdleState::FinalTick()
{
	CGameObject* pPlayer = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Player");
	Vec3 vTargetPos = pPlayer->Transform()->GetRelativePos();
	Vec3 vPos = GetOwner()->Transform()->GetRelativePos();
	Vec3 vDir = vTargetPos - vPos;
	float Dist = sqrt(vDir.x * vDir.x + vDir.y * vDir.y);

	// ChangeState
	if (Dist <= m_AttackRange)
		GetFSM()->ChangeState(L"AttackState");
	else if (Dist <= m_DetectRange)
		GetFSM()->ChangeState(L"MoveState");
}

void CIdleState::Exit()
{
}


