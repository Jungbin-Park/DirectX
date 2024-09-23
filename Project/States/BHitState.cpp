#include "pch.h"
#include "BHitState.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CTransform.h>
#include <Engine/CRenderComponent.h>
#include <Engine/CTimeMgr.h>

BHitState::BHitState()
	: CState(STATE_TYPE::BOSSHITSTATE)
	, m_HitTime(0.f)
	, m_KnockBackSpeed(100.f)
	, m_KnockBackTime(0.2f)
	, m_KnockBackAge(0.f)
{
}

BHitState::~BHitState()
{
}



void BHitState::Enter()
{
	m_HitTime = 0;
	m_KnockBackAge = 0.f;

	CGameObject* pPlayer = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Player");
	Vec3 vTargetPos = pPlayer->Transform()->GetRelativePos();
	Vec3 vPos = GetOwner()->Transform()->GetRelativePos();
	Vec3 vDir = vTargetPos - vPos;
	float Dist = sqrt(vDir.x * vDir.x + vDir.y * vDir.y);
	vDir.Normalize();

	GetOwner()->FlipBookComponent()->Play(2, 10, false);

	// ��������� ����
	GetOwner()->GetRenderComponent()->GetDynamicMaterial()->SetScalarParam(SCALAR_PARAM::INT_0, 1);
}

void BHitState::FinalTick()
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
		GetFSM()->ChangeState(L"BIdleState");
	}
}

void BHitState::Exit()
{
	GetOwner()->FlipBookComponent()->Reset();
}

void BHitState::KnockBack()
{
	// �˹�
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

