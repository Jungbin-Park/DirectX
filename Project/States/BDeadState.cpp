#include "pch.h"
#include "BDeadState.h"

BDeadState::BDeadState()
	: CState(STATE_TYPE::BOSSDEADSTATE)
{
}

BDeadState::~BDeadState()
{
}

void BDeadState::Enter()
{
	GetOwner()->FlipBookComponent()->Play(3, 5, false);
}

void BDeadState::FinalTick()
{
}

void BDeadState::Exit()
{
}


