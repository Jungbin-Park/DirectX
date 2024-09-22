#include "pch.h"
#include "CManagerScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

CManagerScript::CManagerScript()
	: CScript(SCRIPT_TYPE::MANAGERSCRIPT)
	, m_Score(0)
	, m_GateHPref(nullptr)
	, m_GateVPref(nullptr)
	, m_bGate(false)
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
	if (m_Score == 4)
		GateOpen();
}


void CManagerScript::GateClose()
{
	m_bGate = true;
	Instantiate(m_GateVPref, 1, Vec3(-390.f, 20.f, 100.f), L"GateVertical");
}

void CManagerScript::GateOpen()
{
	if (m_bGate)
	{
		m_bGate = false;
		DeleteObject(CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"GateVertical"));
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


