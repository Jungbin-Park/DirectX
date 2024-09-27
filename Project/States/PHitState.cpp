#include "pch.h"
#include "PHitState.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CTransform.h>
#include <Engine/CRenderComponent.h>
#include <Engine/CTimeMgr.h>

PHitState::PHitState()
	: CState(STATE_TYPE::PLAYERHITSTATE)
	, m_HitTime(0.f)
	, m_KnockBackSpeed(100.f)
	, m_KnockBackTime(0.2f)
	, m_KnockBackAge(0.f)
{
}

PHitState::~PHitState()
{
}

void PHitState::Enter()
{
	GetOwner()->FlipBookComponent()->Play(15, 10, false);

	m_HitTime = 0;
	m_KnockBackAge = 0.f;

	CGameObject* pBoss = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Boss");
	Vec3 vTargetPos = pBoss->Transform()->GetRelativePos();
	Vec3 vPos = GetOwner()->Transform()->GetRelativePos();
	Vec3 vDir = vTargetPos - vPos;
	float Dist = sqrt(vDir.x * vDir.x + vDir.y * vDir.y);
	vDir.Normalize();

	// 상수데이터 전달
	GetOwner()->GetRenderComponent()->GetDynamicMaterial()->SetScalarParam(SCALAR_PARAM::INT_0, 1);
}

void PHitState::FinalTick()
{
	CGameObject* pPlayer = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Player");
	Vec3 vTargetPos = pPlayer->Transform()->GetRelativePos();
	Vec3 vPos = GetOwner()->Transform()->GetRelativePos();
	Vec3 vDir = vTargetPos - vPos;

	vDir.Normalize();

	if (m_KnockBackAge < m_KnockBackTime)
	{
		m_KnockBackAge += DT;
		vPos -= vDir * m_KnockBackSpeed * DT;
	}

	GetOwner()->Transform()->SetRelativePos(vPos);

	m_HitTime += DT;

	if (m_HitTime > 0.1f)
		GetOwner()->GetRenderComponent()->GetDynamicMaterial()->SetScalarParam(SCALAR_PARAM::INT_0, 0);

	if (m_HitTime > 0.3f)
	{

	}
}

void PHitState::KnockBack()
{
}

void PHitState::Exit()
{
}


