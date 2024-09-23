#include "pch.h"
#include "CStateMgr.h"

#include "BDashState.h"
#include "BDeadState.h"
#include "BHitState.h"
#include "BIdleState.h"
#include "BLanceState.h"
#include "BReadyState.h"
#include "BSlashState.h"
#include "BSpawnState.h"
#include "BWaterState.h"
#include "CAttackState.h"
#include "CDeadState.h"
#include "CHitState.h"
#include "CIdleState.h"
#include "CMoveState.h"

void CStateMgr::GetStateInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"BDashState");
	_vec.push_back(L"BDeadState");
	_vec.push_back(L"BHitState");
	_vec.push_back(L"BIdleState");
	_vec.push_back(L"BLanceState");
	_vec.push_back(L"BReadyState");
	_vec.push_back(L"BSlashState");
	_vec.push_back(L"BSpawnState");
	_vec.push_back(L"BWaterState");
	_vec.push_back(L"CAttackState");
	_vec.push_back(L"CDeadState");
	_vec.push_back(L"CHitState");
	_vec.push_back(L"CIdleState");
	_vec.push_back(L"CMoveState");
}

CState * CStateMgr::GetState(const wstring& _strStateName)
{
	if (L"BDashState" == _strStateName)
		return new BDashState;
	if (L"BDeadState" == _strStateName)
		return new BDeadState;
	if (L"BHitState" == _strStateName)
		return new BHitState;
	if (L"BIdleState" == _strStateName)
		return new BIdleState;
	if (L"BLanceState" == _strStateName)
		return new BLanceState;
	if (L"BReadyState" == _strStateName)
		return new BReadyState;
	if (L"BSlashState" == _strStateName)
		return new BSlashState;
	if (L"BSpawnState" == _strStateName)
		return new BSpawnState;
	if (L"BWaterState" == _strStateName)
		return new BWaterState;
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
	case (UINT)STATE_TYPE::BOSSDASHSTATE:
		return new BDashState;
		break;
	case (UINT)STATE_TYPE::BOSSDEADSTATE:
		return new BDeadState;
		break;
	case (UINT)STATE_TYPE::BOSSHITSTATE:
		return new BHitState;
		break;
	case (UINT)STATE_TYPE::BOSSIDLESTATE:
		return new BIdleState;
		break;
	case (UINT)STATE_TYPE::BOSSLANCESTATE:
		return new BLanceState;
		break;
	case (UINT)STATE_TYPE::BOSSREADYSTATE:
		return new BReadyState;
		break;
	case (UINT)STATE_TYPE::BOSSSLASHSTATE:
		return new BSlashState;
		break;
	case (UINT)STATE_TYPE::BOSSSPAWNSTATE:
		return new BSpawnState;
		break;
	case (UINT)STATE_TYPE::BOSSWATERSTATE:
		return new BWaterState;
		break;
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
	case STATE_TYPE::BOSSDASHSTATE:
		return L"BDashState";
		break;

	case STATE_TYPE::BOSSDEADSTATE:
		return L"BDeadState";
		break;

	case STATE_TYPE::BOSSHITSTATE:
		return L"BHitState";
		break;

	case STATE_TYPE::BOSSIDLESTATE:
		return L"BIdleState";
		break;

	case STATE_TYPE::BOSSLANCESTATE:
		return L"BLanceState";
		break;

	case STATE_TYPE::BOSSREADYSTATE:
		return L"BReadyState";
		break;

	case STATE_TYPE::BOSSSLASHSTATE:
		return L"BSlashState";
		break;

	case STATE_TYPE::BOSSSPAWNSTATE:
		return L"BSpawnState";
		break;

	case STATE_TYPE::BOSSWATERSTATE:
		return L"BWaterState";
		break;

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