#include "pch.h"
#include "CTriggerScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

#include "CManagerScript.h"

CTriggerScript::CTriggerScript()
	: CScript(SCRIPT_TYPE::TRIGGERSCRIPT)
{
}

CTriggerScript::~CTriggerScript()
{
}

void CTriggerScript::Begin()
{
}

void CTriggerScript::Tick()
{
}

void CTriggerScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider)
{
	Vec3 vPos = Transform()->GetRelativePos();
	Vec3 vLT = Vec3(vPos.x - 200.f, vPos.y + 200.f, 100.f);
	Vec3 vRT = Vec3(vPos.x + 200.f, vPos.y + 200.f, 100.f);
	Vec3 vLB = Vec3(vPos.x - 200.f, vPos.y - 200.f, 100.f);
	Vec3 vRB = Vec3(vPos.x + 200.f, vPos.y - 200.f, 100.f);
	Instantiate(CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\GhoulSpawner.pref"), 2, vLT, L"GhoulSpawner");
	Instantiate(CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\GhoulSpawner.pref"), 2, vRT, L"GhoulSpawner");
	Instantiate(CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\GhoulSpawner.pref"), 2, vLB, L"GhoulSpawner");
	Instantiate(CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\GhoulSpawner.pref"), 2, vRB, L"GhoulSpawner");

	CGameObject* pManager = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"GameManager");
	CManagerScript* pScript = (CManagerScript*)pManager->GetScriptByName(L"ManagerScript");
	pScript->GateClose();

	DeleteObject(GetOwner());
}

void CTriggerScript::SaveToFile(FILE* _File)
{
}

void CTriggerScript::LoadFromFile(FILE* _File)
{
}



