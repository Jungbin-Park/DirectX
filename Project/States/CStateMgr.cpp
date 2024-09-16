#include "pch.h"
#include "CStateMgr.h"

#include "AttackState.h"
#include "DeadState.h"
#include "HitState.h"
#include "IdleState.h"
#include "MoveState.h"

void CStateMgr::GetStateInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"AttackState");
	_vec.push_back(L"DeadState");
	_vec.push_back(L"HitState");
	_vec.push_back(L"IdleState");
	_vec.push_back(L"MoveState");
}

CState * CStateMgr::GetState(const wstring& _strStateName)
{
	if (L"AttackState" == _strStateName)
		return new AttackState;
	if (L"DeadState" == _strStateName)
		return new DeadState;
	if (L"HitState" == _strStateName)
		return new HitState;
	if (L"IdleState" == _strStateName)
		return new IdleState;
	if (L"MoveState" == _strStateName)
		return new MoveState;
	return nullptr;
}

CState * CStateMgr::GetState(UINT _iStateType)
{
	switch (_iStateType)
	{
	case (UINT)STATE_TYPE::ATTACKSTATE:
		return new AttackState;
		break;
	case (UINT)STATE_TYPE::DEADSTATE:
		return new DeadState;
		break;
	case (UINT)STATE_TYPE::HITSTATE:
		return new HitState;
		break;
	case (UINT)STATE_TYPE::IDLESTATE:
		return new IdleState;
		break;
	case (UINT)STATE_TYPE::MOVESTATE:
		return new MoveState;
		break;
	}
	return nullptr;
}

const wchar_t * CStateMgr::GetStateName(CState * _pState)
{
	switch ((STATE_TYPE)_pState->GetStateType())
	{
	case STATE_TYPE::ATTACKSTATE:
		return L"AttackState";
		break;

	case STATE_TYPE::DEADSTATE:
		return L"DeadState";
		break;

	case STATE_TYPE::HITSTATE:
		return L"HitState";
		break;

	case STATE_TYPE::IDLESTATE:
		return L"IdleState";
		break;

	case STATE_TYPE::MOVESTATE:
		return L"MoveState";
		break;

	}
	return nullptr;
}