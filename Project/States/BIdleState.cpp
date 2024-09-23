#include "pch.h"
#include "BIdleState.h"

BIdleState::BIdleState()
	: CState(STATE_TYPE::BOSSIDLESTATE)
{
}

BIdleState::~BIdleState()
{
}

void BIdleState::Enter()
{
	GetOwner()->FlipBookComponent()->Play(1, 10, false);
}

void BIdleState::FinalTick()
{
	
}

void BIdleState::Exit()
{
	GetOwner()->FlipBookComponent()->Reset();
}


