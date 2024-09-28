#include "pch.h"
#include "CManagerScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CTimeMgr.h>
#include <Engine/CFSM.h>
#include <Engine/CState.h>

#include <States/CStateMgr.h>

CManagerScript::CManagerScript()
	: CScript(SCRIPT_TYPE::MANAGERSCRIPT)
	, m_Score(0)
	, m_GateHPref(nullptr)
	, m_GateVPref(nullptr)
	, m_bGate(false)
	, m_Player(nullptr)
	, m_Boss(nullptr)
{
	SetName(L"ManagerScript");
}

CManagerScript::~CManagerScript()
{
}



void CManagerScript::Begin()
{
	m_GateVPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\GateVertical.pref");
	m_GateHPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\GateHorizontal.pref");
	
}

void CManagerScript::Tick()
{
	m_Player = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Player");
	m_Boss = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Boss");

	if (m_Score == 4)
		GateOpen();

	if (m_Player != nullptr)
	{
		if (m_Player->IsDead())
		{
			CTimeMgr::GetInst()->SetDTRatio(0.3f);
		}
	}
	if (m_Boss != nullptr)
	{
		if (m_Boss->FSM()->GetCurState()->GetStateType() == STATE_TYPE::BOSSDEADSTATE)
		{
			CTimeMgr::GetInst()->SetDTRatio(0.3f);
		}
	}
}


void CManagerScript::GateClose()
{
	m_bGate = true;
	Instantiate(m_GateVPref, 1, Vec3(-390.f, 20.f, 100.f), L"GateVertical");
	Instantiate(m_GateHPref, 1, Vec3(-7.f, 485.f, 100.f), L"GateHorizontal");
}

void CManagerScript::GateOpen()
{
	if (m_bGate)
	{
		m_bGate = false;
		DeleteObject(CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"GateVertical"));
		DeleteObject(CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"GateHorizontal"));
	}
	
}

void CManagerScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider)
{
}

void CManagerScript::SaveToFile(FILE* _File)
{
}

void CManagerScript::LoadFromFile(FILE* _File)
{
}


