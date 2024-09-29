#include "pch.h"
#include "CMoveState.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CTransform.h>
#include <Engine/CTimeMgr.h>
#include <Engine/CAssetMgr.h>

CMoveState::CMoveState()
	: CState(STATE_TYPE::MOVESTATE)
	, m_bPlayRightAnim(false)
	, m_bPlayLeftAnim(false)
	, m_Speed(200.f)
	, m_AttackRange(100.f)
	, m_WalkSound(nullptr)
{
}

CMoveState::~CMoveState()
{
}

void CMoveState::Enter()
{
	m_WalkSound = CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\GhoulWalk.mp3");
	m_WalkSound->Play(0, 0.1f, true);

	m_bPlayLeftAnim = false;
	m_bPlayRightAnim = false;
}

void CMoveState::FinalTick()
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
			GetOwner()->FlipBookComponent()->Play(5, 10, true);
		}
	}
	else
	{
		m_bPlayRightAnim = false;
		if (!m_bPlayLeftAnim)
		{
			m_bPlayLeftAnim = true;
			GetOwner()->FlipBookComponent()->Play(4, 10, true);
		}
	}


	// Move
	vPos += vDir * m_Speed * DT;
	GetOwner()->Transform()->SetRelativePos(vPos);


	// ChangeState
	if (Dist <= m_AttackRange)
		GetFSM()->ChangeState(L"AttackState");
}

void CMoveState::Exit()
{
	m_WalkSound->Stop();
}


