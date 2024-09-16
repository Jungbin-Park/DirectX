#include "pch.h"
#include "IdleState.h"

IdleState::IdleState(UINT _StateType)
	:CState(STATE_TYPE::IDLESTATE)
{
}

IdleState::~IdleState()
{
}

void IdleState::Enter()
{
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


