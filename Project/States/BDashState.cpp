#include "pch.h"
#include "BDashState.h"

#include <Engine/CTransform.h>
#include <Engine/CGameObject.h>
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CAssetMgr.h>
#include <Engine/CTimeMgr.h>

BDashState::BDashState()
	: CState(STATE_TYPE::BOSSDASHSTATE)
	, m_bDash(false)
	, m_bTimerStart(true)
	, m_Time(0.f)
	, m_DashSound(nullptr)
{

}

BDashState::~BDashState()
{
}

void BDashState::Enter()
{
	m_DashSound = CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\IceDash.wav");
	m_DashSound->Play(1, 0.3f, false);

	GetOwner()->FlipBookComponent()->Play(4, 10, false);

	Vec3 vPos = GetOwner()->Transform()->GetRelativePos();
	m_TargetPos = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Player")->Transform()->GetRelativePos();
	Vec3 vDir = m_TargetPos - vPos;
	vDir.Normalize();
	m_Dir = vDir;

	m_Time = 0.f;
}

void BDashState::FinalTick()
{
	if (m_bTimerStart)
	{
		m_Time += DT;

		if (m_Time >= 1.f)
		{
			m_bDash = true;
			m_bTimerStart = false;
			m_Time = 0.f;
		}
	}
	
	if (m_bDash)
	{
		GetOwner()->FlipBookComponent()->Play(6, 10, false);
		Vec3 vPos = GetOwner()->Transform()->GetRelativePos();
		Vec3 curDir = m_TargetPos - vPos;
		curDir.Normalize();

		if (fabs(curDir.x - m_Dir.x) < 0.001f && fabs(curDir.y - m_Dir.y) < 0.001f)
		{
			vPos += m_Dir * 1000.f * DT;

			GetOwner()->Transform()->SetRelativePos(vPos);
		}
		else
		{
			GetOwner()->FSM()->ChangeState(L"BSlashState");
		}
	}
	
}

void BDashState::Exit()
{
	GetOwner()->FlipBookComponent()->Reset();
	m_DashSound->Stop();
}


