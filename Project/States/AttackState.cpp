#include "pch.h"
#include "AttackState.h"

AttackState::AttackState(UINT _StateType)
	: CState(STATE_TYPE::ATTACKSTATE)
{
}

AttackState::~AttackState()
{
}

void AttackState::Enter()
{
}

void AttackState::FinalTick()
{
}

void AttackState::Exit()
{
}

void AttackState::SaveToFile(FILE* _File)
{
}

void AttackState::LoadFromFile(FILE* _File)
{
}



