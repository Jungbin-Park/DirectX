#include "pch.h"
#include "CStateMgr.h"

#include "CAttackState.h"
#include "CDeadState.h"
#include "CHitState.h"
#include "CIdleState.h"
#include "CMoveState.h"

void CStateMgr::GetStateInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"CAttackState");
	_vec.push_back(L"CDeadState");
	_vec.push_back(L"CHitState");
	_vec.push_back(L"CIdleState");
	_vec.push_back(L"CMoveState");
}

CState * CStateMgr::GetState(const wstring& _strStateName)
{
	if (L"CAttackState" == _strStateName)
		return new CAttackState;
	if (L"CDeadState" == _strStateName)
		return new CDeadState;
	if (L"CHitState" == _strStateName)
		return new CHitState;
	if (L"CIdleState" == _strStateName)
		return new CIdleState;
	if (L"CMoveState" == _strStateName)
		return new CMoveState;
	return nullptr;
}

CState * CStateMgr::GetState(UINT _iStateType)
{
	switch (_iStateType)
	{
	case (UINT)STATE_TYPE::ATTACKSTATE:
		return new CAttackState;
		break;
	case (UINT)STATE_TYPE::DEADSTATE:
		return new CDeadState;
		break;
	case (UINT)STATE_TYPE::HITSTATE:
		return new CHitState;
		break;
	case (UINT)STATE_TYPE::IDLESTATE:
		return new CIdleState;
		break;
	case (UINT)STATE_TYPE::MOVESTATE:
		return new CMoveState;
		break;
	}
	return nullptr;
}

const wchar_t * CStateMgr::GetStateName(CState * _pState)
{
	switch ((STATE_TYPE)_pState->GetStateType())
	{
	case STATE_TYPE::ATTACKSTATE:
		return L"CAttackState";
		break;

	case STATE_TYPE::DEADSTATE:
		return L"CDeadState";
		break;

	case STATE_TYPE::HITSTATE:
		return L"CHitState";
		break;

	case STATE_TYPE::IDLESTATE:
		return L"CIdleState";
		break;

	case STATE_TYPE::MOVESTATE:
		return L"CMoveState";
		break;

	}
	return nullptr;
}