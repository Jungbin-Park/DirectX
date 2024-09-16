#include "pch.h"
#include "MoveState.h"

MoveState::MoveState(UINT _StateType)
	: CState(STATE_TYPE::MOVESTATE)
{
}

MoveState::~MoveState()
{
}

void MoveState::Enter()
{
}

void MoveState::FinalTick()
{
}

void MoveState::Exit()
{
}

void MoveState::SaveToFile(FILE* _File)
{
}

void MoveState::LoadFromFile(FILE* _File)
{
}



