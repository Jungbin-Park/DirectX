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
{

}

BDashState::~BDashState()
{
}

void BDashState::Enter()
{
	Vec3 vPos = GetOwner()->Transform()->GetRelativePos();
	m_TargetPos = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Player")->Transform()->GetRelativePos();
	Vec3 vDir = m_TargetPos - vPos;
	vDir.Normalize();
	m_Dir = vDir;
}

void BDashState::FinalTick()
{
	Vec3 vPos = GetOwner()->Transform()->GetRelativePos();
	Vec3 curDir = m_TargetPos - vPos;
	curDir.Normalize();

	if(vPos.x )

	vPos += m_Dir * 700.f * DT;

	GetOwner()->Transform()->SetRelativePos(vPos);

}

void BDashState::Exit()
{
}


