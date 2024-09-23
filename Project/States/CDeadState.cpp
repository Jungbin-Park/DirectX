#include "pch.h"
#include "CDeadState.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CTransform.h>
#include <Engine/CTimeMgr.h>
#include <Engine/CCollider2D.h>

CDeadState::CDeadState()
	:CState(STATE_TYPE::BOSSDEADSTATE)
{
}

CDeadState::~CDeadState()
{
}

void CDeadState::Enter()
{
	// 콜라이더 비활성화
	//GetOwner()->Collider2D()->SetActive(false);

	CGameObject* pPlayer = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Player");
	Vec3 vTargetPos = pPlayer->Transform()->GetRelativePos();
	Vec3 vPos = GetOwner()->Transform()->GetRelativePos();
	Vec3 vDir = vTargetPos - vPos;
	float Dist = sqrt(vDir.x * vDir.x + vDir.y * vDir.y);
	vDir.Normalize();

	if (vDir.x > 0)
		GetOwner()->FlipBookComponent()->Play(9, 10, false);
	else
		GetOwner()->FlipBookComponent()->Play(8, 10, false);
}

void CDeadState::FinalTick()
{
	if (GetOwner()->FlipBookComponent()->IsFinish())
		DeleteObject(GetOwner());
}

void CDeadState::Exit()
{
}


