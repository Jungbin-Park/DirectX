#include "pch.h"
#include "IdleState.h"

#include <Engine/CFlipBookComponent.h>

IdleState::IdleState()
	:CState(STATE_TYPE::IDLESTATE)
{
}

IdleState::~IdleState()
{
}

void IdleState::Enter()
{
	//GetOwner()->FlipBookComponent()->Play(0, 10, false);
}

void IdleState::FinalTick()
{
}

void IdleState::Exit()
{
}

void IdleState::SaveToFile(FILE* _File)
{
}

void IdleState::LoadFromFile(FILE* _File)
{
}


