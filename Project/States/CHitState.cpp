#include "pch.h"
#include "CHitState.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CTransform.h>
#include <Engine/CTimeMgr.h>

CHitState::CHitState()
	: CState(STATE_TYPE::HITSTATE)
	, m_HitTime(0.f)
{
}

CHitState::~CHitState()
{
}

void CHitState::KnockBack()
{
}

void CHitState::Enter()
{
	m_HitTime = 0;

	CGameObject* pPlayer = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Player");
	Vec3 vTargetPos = pPlayer->Transform()->GetRelativePos();
	Vec3 vPos = GetOwner()->Transform()->GetRelativePos();
	Vec3 vDir = vTargetPos - vPos;
	float Dist = sqrt(vDir.x * vDir.x + vDir.y * vDir.y);
	vDir.Normalize();

	if (vDir.x > 0)
		GetOwner()->FlipBookComponent()->Play(7, 10, false);
	else
		GetOwner()->FlipBookComponent()->Play(6, 10, false);

}

void CHitState::FinalTick()
{
	m_HitTime += DT;
	if (m_HitTime > 0.5f)
		GetFSM()->ChangeState(L"MoveState");
}

void CHitState::Exit()
{
}


