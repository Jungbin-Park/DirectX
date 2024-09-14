#include "pch.h"
#include "CStateMgr.h"

#include <Engine/CState.h>

void CStateMgr::GetStateInfo(vector<wstring>& _vec)
{
}

CState * CStateMgr::GetState(const wstring& _strStateName)
{
	return nullptr;
}

CState * CStateMgr::GetState(UINT _iStateType)
{
	switch (_iStateType)
	{
	}
	return nullptr;
}

const wchar_t * CStateMgr::GetStateName(CState * _pState)
{
	switch ((STATE_TYPE)_pState->GetStateType())
	{
	}
	return nullptr;
}