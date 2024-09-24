#include "pch.h"
#include "CState.h"

#include "CTransform.h"

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

CGameObject* CState::InstantiateSkill(Ptr<CPrefab> _Pref, int _LayerIdx, Vec3 _WorldPos, const wstring& _Name)
{
	CGameObject* pInst = _Pref->Instantiate();

	pInst->SetName(_Name);
	pInst->Transform()->SetRelativePos(_WorldPos);

	CreateObject(pInst, _LayerIdx);

	return pInst;
}
