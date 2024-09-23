#include "pch.h"
#include "BSpawnState.h"

#include <Engine/CTransform.h>
#include <Engine/CScript.h>
#include <Engine/CTimeMgr.h>


BSpawnState::BSpawnState()
	: CState(STATE_TYPE::BOSSSPAWNSTATE)
{
}

BSpawnState::~BSpawnState()
{
}

void BSpawnState::Enter()
{
	GetOwner()->FlipBookComponent()->Play(0, 3, false);
}

void BSpawnState::FinalTick()
{
	if (GetOwner()->FlipBookComponent()->IsFinish())
		GetFSM()->ChangeState(L"BIdleState");
}

void BSpawnState::Exit()
{
	GetOwner()->FlipBookComponent()->Reset();
}


