#include "pch.h"
#include "CStateMgr.h"

#include "CIdleState.h"

void CStateMgr::GetStateInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"CIdleState");
}

CState * CStateMgr::GetState(const wstring& _strStateName)
{
	if (L"CIdleState" == _strStateName)
		return new CIdleState;
	return nullptr;
}

CState * CStateMgr::GetState(UINT _iStateType)
{
	switch (_iStateType)
	{
	case (UINT)STATE_TYPE::IDLESTATE:
		return new CIdleState;
		break;
	}
	return nullptr;
}

const wchar_t * CStateMgr::GetStateName(CState * _pState)
{
	switch ((STATE_TYPE)_pState->GetStateType())
	{
	case STATE_TYPE::IDLESTATE:
		return L"CIdleState";
		break;

	}
	return nullptr;
}