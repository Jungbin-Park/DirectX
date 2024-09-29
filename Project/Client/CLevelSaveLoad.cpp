#include "pch.h"
#include "CLevelSaveLoad.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CLayer.h>
#include <Engine/CState.h>
#include <Engine/CGameObject.h>
#include <Engine/components.h>
#include <Engine/CCollisionMgr.h>

#include <Scripts/CScriptMgr.h>
#include <Scripts/CManagerScript.h>
#include <Scripts/CPlayerHUDScript.h>

#include <States/CStateMgr.h>

#include "CTestLevel.h"

void CLevelSaveLoad::SaveLevel(const wstring& _FilePath, CLevel* _Level)
{
	assert(_Level && _Level->GetState() == LEVEL_STATE::STOP);

	FILE* File = nullptr;
	_wfopen_s(&File, _FilePath.c_str(), L"wb");

	// Level 이름 저장
	SaveWString(_Level->GetName(), File);

	// Level 안에 있는 Layer 를 저장
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		CLayer* pLayer = _Level->GetLayer(i);

		// Layer 이름 저장
		SaveWString(pLayer->GetName(), File);

		// Layer 안에 있는 GameObject 를 저장
		const vector<CGameObject*>& vecParents = pLayer->GetParentObjects();

		// Layer 가 보유한 ParentObject 개수 저장
		size_t count = vecParents.size();
		fwrite(&count, sizeof(size_t), 1, File);

		// GameObject 저장
		for (size_t i = 0; i < vecParents.size(); ++i)
		{
			SaveGameObject(File, vecParents[i]);
		}
	}

	fclose(File);
}

void CLevelSaveLoad::SaveGameObject(FILE* _File, CGameObject* _Object)
{
	// GameObject 의 이름 저장
	SaveWString(_Object->GetName(), _File);

	// Component 정보 저장
	UINT i = 0;
	for (; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		CComponent* pComponent = _Object->GetComponent((COMPONENT_TYPE)i);

		if (nullptr == pComponent)
			continue;

		// ComponentType 을 저장
		COMPONENT_TYPE Type = pComponent->GetComponentType();
		fwrite(&Type, sizeof(COMPONENT_TYPE), 1, _File);

		pComponent->SaveToFile(_File);
	}

	// COMPONENT_TYPE::END 저장
	fwrite(&i, sizeof(COMPONENT_TYPE), 1, _File);

	// Script 정보 저장
	// Script 개수 저장
	const vector<CScript*> vecScripts = _Object->GetScripts();
	size_t ScriptCount = vecScripts.size();
	fwrite(&ScriptCount, sizeof(size_t), 1, _File);

	for (size_t i = 0; i < ScriptCount; ++i)
	{
		// Script 의 이름 저장
		wstring ScriptName = CScriptMgr::GetScriptName(vecScripts[i]);
		SaveWString(ScriptName, _File);

		// Script 정보 저장
		vecScripts[i]->SaveToFile(_File);
	}

	// Child 정보 저장
	const vector<CGameObject*>& vecChild = _Object->GetChildren();
	size_t ChildCount = vecChild.size();
	fwrite(&ChildCount, sizeof(size_t), 1, _File);

	for (size_t i = 0; i < vecChild.size(); ++i)
	{
		SaveGameObject(_File, vecChild[i]);
	}
}

void CLevelSaveLoad::LevelInit()
{
	/*wstring levelName = L"Boss";
	wstring StrLevelLoadPath = CPathMgr::GetInst()->GetContentPath();
	StrLevelLoadPath += (L"level\\" + levelName + L".lv");
	CLevelSaveLoad::LoadLevel(StrLevelLoadPath);
	levelName = L"Ice";
	wstring StrLevelLoadPath = CPathMgr::GetInst()->GetContentPath();
	StrLevelLoadPath += (L"level\\" + levelName + L".lv");
	CLevelSaveLoad::LoadLevel(StrLevelLoadPath);*/
	wstring levelName = L"Home";
	wstring StrLevelLoadPath = CPathMgr::GetInst()->GetContentPath();
	StrLevelLoadPath += (L"level\\" + levelName + L".lv");
	CLevel* pLevel = CLevelSaveLoad::LoadLevel(StrLevelLoadPath); 

	CCollisionMgr::GetInst()->CollisionCheck(1, 3); // Platform vs Player
	CCollisionMgr::GetInst()->CollisionCheck(1, 4); // Platform vs Monster
	CCollisionMgr::GetInst()->CollisionCheck(1, 6); // Platform vs Monster Projectile
	CCollisionMgr::GetInst()->CollisionCheck(1, 5); // Platform vs Player Projectile

	CCollisionMgr::GetInst()->CollisionCheck(5, 4); // Player Projectile vs Monster
	CCollisionMgr::GetInst()->CollisionCheck(6, 3); // Monster Projectile vs player
	CCollisionMgr::GetInst()->CollisionCheck(2, 3); // Monster Projectile vs player
	CCollisionMgr::GetInst()->CollisionCheck(7, 3); // Object vs player

	/*CGameObject* puicam = pLevel->FindObjectByName(L"UICamera");
	pLevel->GetLayer(0)->DisconnectWithObject(puicam);

	CGameObject* phud = pLevel->FindObjectByName(L"PlayerHUD");
	pLevel->GetLayer(31)->DisconnectWithObject(phud);
	*/
	/*CGameObject* phud = pLevel->FindObjectByName(L"PlayerHPBar");
	pLevel->GetLayer(31)->DisconnectWithObject(phud);

	CGameObject* pHPBar = new CGameObject;
	pHPBar->SetName(L"PlayerHPBar");

	pHPBar->AddComponent(new CTransform);
	pHPBar->AddComponent(new CMeshRender);
	pHPBar->AddComponent(new CPlayerHUDScript);

	pHPBar->Transform()->SetRelativePos(-480.f, 305.f, 4.f);
	pHPBar->Transform()->SetRelativeScale(130.f, 25.f, 0.f);

	pHPBar->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pHPBar->MeshRender()->SetMaterial(CAssetMgr::GetInst()->Load<CMaterial>(L"material\\PlayerHUD.mtrl", L"material\\PlayerHUD.mtrl"));

	pLevel->AddObject(31, pHPBar);*/

	//// BossStatus
	//CGameObject* pHUD = new CGameObject;
	//pHUD->SetName(L"BossHUD");

	//pHUD->AddComponent(new CTransform);
	//pHUD->AddComponent(new CMeshRender);

	//pHUD->Transform()->SetRelativePos(-500.f, 300.f, 5.f);
	//pHUD->Transform()->SetRelativeScale(168.f, 44.f, 0.f);

	//pHUD->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	//pHUD->MeshRender()->SetMaterial(CAssetMgr::GetInst()->Load<CMaterial>(L"material\\PlayerStatus.mtrl", L"material\\PlayerStatus.mtrl"));

	//pLevel->AddObject(31, pHUD);


	//// BossHPBar
	//CGameObject* pHPBar = new CGameObject;
	//pHPBar->SetName(L"BossHPBar");

	//pHPBar->AddComponent(new CTransform);
	//pHPBar->AddComponent(new CMeshRender);
	//pHPBar->AddComponent(new CPlayerHUDScript);

	//pHPBar->Transform()->SetRelativePos(-480.f, 305.f, 4.f);
	//pHPBar->Transform()->SetRelativeScale(130.f, 25.f, 0.f);

	//pHPBar->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	//pHPBar->MeshRender()->SetMaterial(CAssetMgr::GetInst()->Load<CMaterial>(L"material\\BossHPBar.mtrl", L"material\\BossHPBar.mtrl"));

	//pLevel->AddObject(31, pHPBar);

	ChangeLevel(pLevel, LEVEL_STATE::STOP);
}

CLevel* CLevelSaveLoad::LoadLevel(const wstring& _FilePath)
{
	FILE* File = nullptr;
	_wfopen_s(&File, _FilePath.c_str(), L"rb");

	// Level 생성
	CLevel* pNewLevel = new CLevel;

	// Level 이름 불러오기
	wstring LevelName;
	LoadWString(LevelName, File);
	pNewLevel->SetName(LevelName);

	// Level 안에 있는 Layer 정보 불러오기
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		CLayer* pLayer = pNewLevel->GetLayer(i);

		// Layer 이름 불러오기
		wstring LayerName;
		LoadWString(LayerName, File);
		pLayer->SetName(LayerName);

		// Layer 가 보유한 ParentObject 개수 불어오기
		size_t count = 0;
		fread(&count, sizeof(size_t), 1, File);

		// GameObject 불러와서 Layer 에 집어넣기
		for (size_t i = 0; i < count; ++i)
		{
			CGameObject* pLoadedObject = LoadGameObject(File);
			pLayer->AddObject(pLoadedObject, false);
		}
	}

	fclose(File);

	return pNewLevel;
}

CGameObject* CLevelSaveLoad::LoadGameObject(FILE* _File)
{
	CGameObject* pObject = new CGameObject;

	// GameObject 의 이름 로드
	wstring Name;
	LoadWString(Name, _File);
	pObject->SetName(Name);

	// Component 정보 로드
	COMPONENT_TYPE Type = COMPONENT_TYPE::END;
	while (true)
	{
		// 저장되어있는 정보가 어떤 컴포넌트인지 확인
		fread(&Type, sizeof(COMPONENT_TYPE), 1, _File);

		// 읽은 타입 정보가 END 인 경우, 저장된 컴포넌트 정보의 끝이다.
		if (COMPONENT_TYPE::END == Type)
			break;

		// 저장된 타입에 맞는 컴포넌트를 생성 시키고, 저장할때랑 동일한 순서로 데이터를 읽는다.
		CComponent* pComponent = GetComponent(Type);

		// 생성된 컴포넌트를 오브젝트에 넣어준다.
		pObject->AddComponent(pComponent);

		// 저장당시의 정보를 읽어와서 복수한다.
		pComponent->LoadFromFile(_File);
	}

	// Script 정보 로드	
	size_t ScriptCount = 0;
	fread(&ScriptCount, sizeof(size_t), 1, _File);

	for (size_t i = 0; i < ScriptCount; ++i)
	{
		// Script 의 이름 읽기
		wstring ScriptName;
		LoadWString(ScriptName, _File);

		// 읽은 Script 이름으로 이름에 해당하는 Script 생성
		CScript* pScript = CScriptMgr::GetScript(ScriptName);


		pScript->LoadFromFile(_File);

		pObject->AddComponent(pScript);
	}

	// Child 정보 로드
	size_t ChildCount = 0;
	fread(&ChildCount, sizeof(size_t), 1, _File);

	for (size_t i = 0; i < ChildCount; ++i)
	{
		CGameObject* pChildObject = LoadGameObject(_File);
		pObject->AddChild(pChildObject);
	}

	return pObject;
}

CComponent* CLevelSaveLoad::GetComponent(COMPONENT_TYPE _Type)
{
	switch (_Type)
	{
	case COMPONENT_TYPE::TRANSFORM:
		return new CTransform;

	case COMPONENT_TYPE::COLLIDER2D:
		return new CCollider2D;

	case COMPONENT_TYPE::COLLIDER3D:

		break;
	case COMPONENT_TYPE::LIGHT2D:
		return  new CLight2D;

	case COMPONENT_TYPE::LIGHT3D:
		break;

	case COMPONENT_TYPE::FLIPBOOKCOMPONENT:
		return new CFlipBookComponent;

	case COMPONENT_TYPE::ANIMATOR3D:
		break;

	case COMPONENT_TYPE::FSM:
		return new CFSM;
		break;

	case COMPONENT_TYPE::RIGIDBODY:
		break;

	case COMPONENT_TYPE::CAMERA:
		return  new CCamera;

	case COMPONENT_TYPE::MESHRENDER:
		return  new CMeshRender;

	case COMPONENT_TYPE::TILEMAP:
		return  new CTileMap;

	case COMPONENT_TYPE::PARTICLESYSTEM:
		break;

	case COMPONENT_TYPE::DECAL:
		break;

	case COMPONENT_TYPE::SKYBOX:
		break;

	case COMPONENT_TYPE::LANDSCAPE:
		break;
	}

	return nullptr;
}


