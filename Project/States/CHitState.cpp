#include "pch.h"
#include "CHitState.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CTransform.h>
#include <Engine/CTimeMgr.h>
#include <Engine/CConstBuffer.h>
#include <Engine/CDevice.h>
#include <Engine/CRenderComponent.h>

CHitState::CHitState()
	: CState(STATE_TYPE::HITSTATE)
	, m_HitTime(0.f)
	, m_KnockBackSpeed(100.f)
	, m_KnockBackTime(0.2f)
	, m_KnockBackAge(0.f)
	, m_AttackRange(100.f)
{
}

CHitState::~CHitState()
{
}

void CHitState::Enter()
{
	m_HitTime = 0;
	m_KnockBackAge = 0.f;

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

	// 상수데이터 전달
	GetOwner()->GetRenderComponent()->GetDynamicMaterial()->SetScalarParam(SCALAR_PARAM::INT_0, 1);
}

void CHitState::FinalTick()
{
	KnockBack();

	CGameObject* pPlayer = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Player");
	Vec3 vTargetPos = pPlayer->Transform()->GetRelativePos();
	Vec3 vPos = GetOwner()->Transform()->GetRelativePos();
	Vec3 vDir = vTargetPos - vPos;
	float Dist = sqrt(vDir.x * vDir.x + vDir.y * vDir.y);

	m_HitTime += DT;

	if(m_HitTime > 0.1f)
		GetOwner()->GetRenderComponent()->GetDynamicMaterial()->SetScalarParam(SCALAR_PARAM::INT_0, 0);

	if (m_HitTime > 0.3f)
	{
		GetFSM()->ChangeState(L"IdleState");
	}
}

void CHitState::Exit()
{
	GetOwner()->FlipBookComponent()->Reset();
}

void CHitState::KnockBack()
{
	// 넉백
	CGameObject* pPlayer = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Player");
	Vec3 PlayerPos = pPlayer->Transform()->GetRelativePos();
	Vec3 vPos = GetOwner()->Transform()->GetRelativePos();
	Vec3 vDir = vPos - PlayerPos;
	vDir.Normalize();

	if (m_KnockBackAge < m_KnockBackTime)
	{
		m_KnockBackAge += DT;
		vPos += vDir * m_KnockBackSpeed * DT;
	}

	GetOwner()->Transform()->SetRelativePos(vPos);
}
