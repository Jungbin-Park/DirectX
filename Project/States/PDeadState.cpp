#include "pch.h"
#include "PDeadState.h"

PDeadState::PDeadState()
	: CState(STATE_TYPE::PLAYERDEADSTATE)
{
}

PDeadState::~PDeadState()
{
}

void PDeadState::Enter()
{
	GetOwner()->FlipBookComponent()->Play(15, 5, false);
}

void PDeadState::FinalTick()
{
}

void PDeadState::Exit()
{
}


