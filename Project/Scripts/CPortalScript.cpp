#include "pch.h"
#include "CPortalScript.h"

#include <Engine/CLevel.h>
#include <Engine/CLevelMgr.h>
#include <Engine/CLayer.h>
#include <Engine/CCollisionMgr.h>

#include "CManagerScript.h"

CPortalScript::CPortalScript()
	: CScript(SCRIPT_TYPE::PORTALSCRIPT)
	, m_TeleportPref(nullptr)
{
}

CPortalScript::~CPortalScript()
{
}

void CPortalScript::Begin()
{
	m_TeleportPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\Teleport.pref");
}

void CPortalScript::Tick()
{
}

void CPortalScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider)
{
}

void CPortalScript::Overlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider)
{
	
	if (CLevelMgr::GetInst()->GetCurrentLevel()->GetName() == L"Home")
	{
		if (KEY_TAP(KEY::F))
		{
			Vec3 vPos = Transform()->GetRelativePos();
			vPos.x += 5.f;
			vPos.y += 300.f;
			m_TP = InstantiateSkill(m_TeleportPref, 0, vPos, L"Teleport");
		}
		if (m_TP != nullptr)
		{
			if (m_TP->FlipBookComponent()->IsFinish())
			{
				m_TP = nullptr;
				CGameObject* pManager = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"GameManager");
				CManagerScript* pScript = nullptr;
				pScript = (CManagerScript*)pManager->GetScriptByName(L"ManagerScript");
				wstring levelName = L"Ice";
				wstring StrLevelLoadPath = CPathMgr::GetInst()->GetContentPath();
				StrLevelLoadPath += (L"level\\" + levelName + L".lv");
				CLevel* pLevel = pScript->LoadLevel(StrLevelLoadPath);

				ChangeLevel(pLevel, LEVEL_STATE::PLAY);
			}
			
		}
		
	}
	if (CLevelMgr::GetInst()->GetCurrentLevel()->GetName() == L"Ice")
	{
		if (KEY_TAP(KEY::F))
		{
			Vec3 vPos = Transform()->GetRelativePos();
			vPos.x += 5.f;
			vPos.y += 300.f;
			m_TP = InstantiateSkill(m_TeleportPref, 0, vPos, L"Teleport");
		}
		if (m_TP != nullptr)
		{
			if (m_TP->FlipBookComponent()->IsFinish())
			{
				m_TP = nullptr;
				CGameObject* pManager = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"GameManager");
				CManagerScript* pScript = nullptr;
				pScript = (CManagerScript*)pManager->GetScriptByName(L"ManagerScript");
				wstring levelName = L"Boss";
				wstring StrLevelLoadPath = CPathMgr::GetInst()->GetContentPath();
				StrLevelLoadPath += (L"level\\" + levelName + L".lv");
				CLevel* pLevel = pScript->LoadLevel(StrLevelLoadPath);

				ChangeLevel(pLevel, LEVEL_STATE::PLAY);
			}

		}
	}
}

void CPortalScript::SaveToFile(FILE* _File)
{
}

void CPortalScript::LoadFromFile(FILE* _File)
{
}



