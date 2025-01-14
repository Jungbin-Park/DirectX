#include "pch.h"
#include "MenuUI.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CAssetMgr.h>
#include <Engine/assets.h>
#include <Engine/CGameObject.h>
#include <Engine/CScript.h>

#include <Scripts/CScriptMgr.h>
#include <Scripts/CPlatformScript.h>
#include <Scripts/CSpawnerScript.h>
#include <Scripts/CTriggerScript.h>
#include <Scripts/CPortalScript.h>

#include "CEditorMgr.h"
#include "Inspector.h"
#include "CLevelSaveLoad.h"

MenuUI::MenuUI()
{
}

MenuUI::~MenuUI()
{
}

void MenuUI::Tick()
{
	if (!IsActive())
		return;

	if (ImGui::BeginMainMenuBar())
	{

		Update();

		ImGui::EndMainMenuBar();
	}
}


void MenuUI::Update()
{
	File();

	Level();

	GameObject();

	Assets();
}

void MenuUI::File()
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();

	if (ImGui::BeginMenu("File"))
	{
		if (ImGui::MenuItem("Level Save"))
		{
			wstring levelName = pCurLevel->GetName();
			wstring strLevelPath = CPathMgr::GetInst()->GetContentPath();
			strLevelPath += (L"level\\" + levelName + L".lv");
			CLevelSaveLoad::SaveLevel(strLevelPath, pCurLevel);
		}

		if (ImGui::MenuItem("Level Load"))
		{
			wstring levelName = pCurLevel->GetName();
			wstring StrLevelLoadPath = CPathMgr::GetInst()->GetContentPath();
			StrLevelLoadPath += (L"level\\" + levelName + L".lv");
			CLevel* pLoadedLevel = CLevelSaveLoad::LoadLevel(StrLevelLoadPath);
		}

		ImGui::EndMenu();
	}
}

void MenuUI::Level()
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();

	ImGui::BeginDisabled(!pCurLevel);

	if (ImGui::BeginMenu("Level"))
	{
		LEVEL_STATE State = LEVEL_STATE::STOP;
		if (nullptr != pCurLevel)
			State = pCurLevel->GetState();

		ImGui::BeginDisabled(LEVEL_STATE::PLAY == State);
		if (ImGui::MenuItem("Play"))
		{
			// Stop->Play 전환 시에만 저장
			if (LEVEL_STATE::STOP == State)
			{
				wstring levelName = pCurLevel->GetName();
				wstring strLevelPath = CPathMgr::GetInst()->GetContentPath();
				strLevelPath += (L"level\\" + levelName +  L".lv");
				CLevelSaveLoad::SaveLevel(strLevelPath, pCurLevel);
			}

			ChangeLevelState(LEVEL_STATE::PLAY);
		}
		ImGui::EndDisabled();

		ImGui::BeginDisabled(LEVEL_STATE::PLAY != State);
		if (ImGui::MenuItem("Pause"))
		{
			ChangeLevelState(LEVEL_STATE::PAUSE);
		}
		ImGui::EndDisabled();

		ImGui::BeginDisabled(LEVEL_STATE::STOP == State);
		if (ImGui::MenuItem("Stop"))
		{
			wstring levelName = pCurLevel->GetName();
			wstring StrLevelLoadPath = CPathMgr::GetInst()->GetContentPath();
			StrLevelLoadPath += (L"level\\" + levelName + L".lv");
			CLevel* pLoadedLevel = CLevelSaveLoad::LoadLevel(StrLevelLoadPath);
			ChangeLevel(pLoadedLevel, LEVEL_STATE::STOP);

			// Inspector Clear 하기 (이전 오브젝트 정보를 보여주고 있을 수가 있기 때문에)				
			Inspector* pInspector = (Inspector*)CEditorMgr::GetInst()->FindEditorUI("Inspector");
			pInspector->SetTargetObject(nullptr);
			pInspector->SetTargetAsset(nullptr);
		}
		ImGui::EndDisabled();

		ImGui::EndMenu();
	}

	ImGui::EndDisabled();
}

void MenuUI::GameObject()
{
	if (ImGui::BeginMenu("GameObject"))
	{
		if (ImGui::MenuItem("Create Empty Object"))
		{

		}

		if (ImGui::BeginMenu("Add Component"))
		{
			ImGui::MenuItem("MeshRender");
			ImGui::MenuItem("Collider2D");
			ImGui::MenuItem("Camera");

			ImGui::EndMenu();
		}

		if (ImGui::MenuItem("Create Platform"))
		{
			CGameObject* pPlatform = new CGameObject;
			pPlatform->SetName(L"Platform");
			pPlatform->AddComponent(new CTransform);
			pPlatform->AddComponent(new CCollider2D);
			pPlatform->AddComponent(new CFlipBookComponent);
			pPlatform->AddComponent(new CPlatformScript);
			pPlatform->Transform()->SetRelativePos(0.f, 0.f, 100.f);
			pPlatform->Transform()->SetRelativeScale(150.f, 150.f, 1.f);

			pPlatform->Collider2D()->SetIndependentScale(false);
			pPlatform->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
			pPlatform->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
			CLevelMgr::GetInst()->GetCurrentLevel()->AddObject(1, pPlatform);
		}

		if (ImGui::MenuItem("Create Trigger"))
		{
			CGameObject* pSpawner = new CGameObject;
			pSpawner->SetName(L"Trigger");
			pSpawner->AddComponent(new CTransform);
			pSpawner->AddComponent(new CCollider2D);
			pSpawner->AddComponent(new CFlipBookComponent);
			pSpawner->AddComponent(new CTriggerScript);

			pSpawner->Transform()->SetRelativePos(0.f, 0.f, 100.f);
			pSpawner->Transform()->SetRelativeScale(150.f, 150.f, 1.f);

			pSpawner->Collider2D()->SetIndependentScale(false);
			pSpawner->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
			pSpawner->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));

			CLevelMgr::GetInst()->GetCurrentLevel()->AddObject(1, pSpawner);
		}

		if (ImGui::MenuItem("Create Portal"))
		{
			CGameObject* pPortal = new CGameObject;
			pPortal->SetName(L"Portal");

			pPortal->AddComponent(new CTransform);
			pPortal->AddComponent(new CMeshRender);
			pPortal->AddComponent(new CCollider2D);
			pPortal->AddComponent(new CFlipBookComponent);
			pPortal->AddComponent(new CPortalScript);

			pPortal->Transform()->SetRelativePos(0.f, 0.f, 0.f);
			pPortal->Transform()->SetRelativeScale(200.f, 150.f, 0.f);

			pPortal->Collider2D()->SetIndependentScale(false);
			pPortal->Collider2D()->SetOffset(Vec3(0.0f, 0.7f, 0.f));
			pPortal->Collider2D()->SetScale(Vec3(0.5f, 0.1f, 0.f));

			pPortal->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
			pPortal->MeshRender()->SetMaterial(CAssetMgr::GetInst()->Load<CMaterial>(L"material\\WarpStone.mtrl", L"material\\WarpStone.mtrl"));

			CLevelMgr::GetInst()->GetCurrentLevel()->AddObject(7, pPortal);
		}

		AddScript();

		ImGui::EndMenu();
	}
}

void MenuUI::AddScript()
{
	if (ImGui::BeginMenu("Add Script"))
	{
		vector<wstring> vecScriptsName;
		CScriptMgr::GetScriptInfo(vecScriptsName);

		for (size_t i = 0; i < vecScriptsName.size(); ++i)
		{
			if (ImGui::MenuItem(string(vecScriptsName[i].begin(), vecScriptsName[i].end()).c_str()))
			{
				//CScript* pScript = CScriptMgr::GetScript(vecScriptsName[i]);
				
				// 인스펙터
				Inspector* pInspector = (Inspector*)CEditorMgr::GetInst()->FindEditorUI("Inspector");

				// 타겟 오브젝트 알아냄
				CGameObject* pObject = pInspector->GetTargetObject();
				if (nullptr != pObject)
				{
					// 오브젝트에, 선택한 스크립트를 추가해줌
					CScript* pScript = CScriptMgr::GetScript(vecScriptsName[i]);
					pObject->AddComponent(pScript);
				}
			}
		}

		ImGui::EndMenu();
	}

}

void MenuUI::Assets()
{
	if (ImGui::BeginMenu("Assets"))
	{
		if (ImGui::MenuItem("Create Empty Material"))
		{
			Ptr<CMaterial> pMtrl = new CMaterial;
			wstring Key = GetAssetKey(ASSET_TYPE::MATERIAL, L"Default Material");
			CAssetMgr::GetInst()->AddAsset<CMaterial>(Key, pMtrl);
			pMtrl->Save(Key);
		}

		EditorUI* pSpriteEditor = CEditorMgr::GetInst()->FindEditorUI("SpriteEditor");
		bool IsActiveSE = pSpriteEditor->IsActive();

		if (ImGui::MenuItem("Sprite Editor", nullptr, &IsActiveSE))
		{
			CEditorMgr::GetInst()->FindEditorUI("SpriteEditor")->SetActive(IsActiveSE);
		}

		EditorUI* pFlipBookEditor = CEditorMgr::GetInst()->FindEditorUI("FlipBookEditor");
		bool IsActiveFE = pFlipBookEditor->IsActive();

		if (ImGui::MenuItem("FlipBook Editor", nullptr, &IsActiveFE))
		{
			CEditorMgr::GetInst()->FindEditorUI("FlipBookEditor")->SetActive(IsActiveFE);
		}

		EditorUI* pPlatformEditor = CEditorMgr::GetInst()->FindEditorUI("PlatformEditor");
		bool IsActivePE = pPlatformEditor->IsActive();

		bool IsLevelStop = false;
		if (CLevelMgr::GetInst()->GetCurrentLevel()->GetState() == LEVEL_STATE::STOP)
			IsLevelStop = true;
		else
			IsLevelStop = false;

		if (ImGui::MenuItem("Platform Editor", nullptr, &IsActivePE, IsLevelStop))
		{
			CEditorMgr::GetInst()->FindEditorUI("PlatformEditor")->SetActive(IsActivePE);
		}

		ImGui::EndMenu();
	}
}

wstring MenuUI::GetAssetKey(ASSET_TYPE _Type, const wstring& _KeyFormat)
{
	wstring Key;

	switch (_Type)
	{
	case ASSET_TYPE::MATERIAL:
	{
		Key = wstring(L"material\\") + _KeyFormat + L" %d.mtrl";
	}
	break;
	case ASSET_TYPE::PREFAB:
	{
		Key = wstring(L"prefab\\") + _KeyFormat + L" %d.pref";
	}
	break;
	case ASSET_TYPE::SPRITE:
	{
		Key = wstring(L"sprite\\") + _KeyFormat + L" %d.sprite";
	}
	break;
	case ASSET_TYPE::FLIPBOOK:
	{
		Key = wstring(L"flipbook\\") + _KeyFormat + L" %d.flip";
	}
	break;
	default:
		assert(nullptr);
		break;
	}

	wchar_t szKey[255] = {};
	wstring FilePath = CPathMgr::GetInst()->GetContentPath();

	for (UINT i = 0; i < 0xffffffff; ++i)
	{
		swprintf_s(szKey, 255, Key.c_str(), i);

		if (false == std::filesystem::exists(FilePath + szKey))
		{
			break;
		}
	}

	return szKey;
}
