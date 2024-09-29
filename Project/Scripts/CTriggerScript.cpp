#include "pch.h"
#include "CTriggerScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

#include "CManagerScript.h"
#include "CCameraMoveScript.h"

CTriggerScript::CTriggerScript()
	: CScript(SCRIPT_TYPE::TRIGGERSCRIPT)
	, m_CurLevelName(L"")
{
}

CTriggerScript::~CTriggerScript()
{
}

void CTriggerScript::Begin()
{
	m_CurLevelName = CLevelMgr::GetInst()->GetCurrentLevel()->GetName();
}

void CTriggerScript::Tick()
{
}

void CTriggerScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider)
{
	if (_OtherObject->GetName() == L"Player")
	{
		if (m_CurLevelName == L"Ice")
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
			CManagerScript* pScript = nullptr;
			pScript = (CManagerScript*)pManager->GetScriptByName(L"ManagerScript");
			pScript->GateClose();
		}

		if (m_CurLevelName == L"Boss")
		{
			CGameObject* pManager = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"MainCamera");
			CCameraMoveScript* pScript = nullptr;
			pScript = (CCameraMoveScript*)pManager->GetScriptByName(L"CCameraMoveScript");
			pScript->BossSpawn();

			Vec3 vPos = Vec3(0.f, 1200.f, 100.f);
			Instantiate(CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\Boss.pref"), 4, vPos, L"Boss");

			vPos = Vec3(0.f, 300.f, 5.f);
			Instantiate(CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\BossHUD.pref"), 31, vPos, L"BossHUD");

			vPos = Vec3(1.f, 295.f, 4.f);
			Instantiate(CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\BossHPBar.pref"), 31, vPos, L"BossHPBar");
		}

		DeleteObject(GetOwner());
	}
}

void CTriggerScript::SaveToFile(FILE* _File)
{
}

void CTriggerScript::LoadFromFile(FILE* _File)
{
}



