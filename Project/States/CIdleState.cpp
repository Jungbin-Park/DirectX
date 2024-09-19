#include "pch.h"
#include "CIdleState.h"


CIdleState::CIdleState()
	:CState(STATE_TYPE::IDLESTATE)
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
}

void CIdleState::Exit()
{
}


