#include "pch.h"
#include "DeadState.h"

DeadState::DeadState()
	:CState(STATE_TYPE::DEADSTATE)
{
}

DeadState::~DeadState()
{
}

void DeadState::Enter()
{
}

void DeadState::FinalTick()
{
}

void DeadState::Exit()
{
}

void DeadState::SaveToFile(FILE* _File)
{
}

void DeadState::LoadFromFile(FILE* _File)
{
}



