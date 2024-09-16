#include "pch.h"
#include "CState.h"

CState::CState(UINT _StateType)
	: m_StateType(_StateType)
	, m_Owner(nullptr)
{
}

CState::~CState()
{
}

void CState::ChangeState(const wstring& _strStateName)
{
	m_Owner->ChangeState(_strStateName);
}
