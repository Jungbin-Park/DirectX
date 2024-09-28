#include "pch.h"
#include "CPortalScript.h"

#include <Engine/CLevel.h>
#include <Engine/CLevelMgr.h>
#include <Engine/CLayer.h>
#include <Engine/CCollisionMgr.h>

CPortalScript::CPortalScript()
	: CScript(SCRIPT_TYPE::PORTALSCRIPT)
{
}

CPortalScript::~CPortalScript()
{
}

void CPortalScript::Begin()
{

}

void CPortalScript::Tick()
{
}

CLevel* CPortalScript::LoadLevel(const wstring& _FilePath)
{
	FILE* File = nullptr;
	_wfopen_s(&File, _FilePath.c_str(), L"rb");

	// Level ����
	CLevel* pNewLevel = new CLevel;

	// Level �̸� �ҷ�����
	wstring LevelName;
	LoadWString(LevelName, File);
	pNewLevel->SetName(LevelName);

	// Level �ȿ� �ִ� Layer ���� �ҷ�����
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		CLayer* pLayer = pNewLevel->GetLayer(i);

		// Layer �̸� �ҷ�����
		wstring LayerName;
		LoadWString(LayerName, File);
		pLayer->SetName(LayerName);

		// Layer �� ������ ParentObject ���� �Ҿ����
		size_t count = 0;
		fread(&count, sizeof(size_t), 1, File);

		// GameObject �ҷ��ͼ� Layer �� ����ֱ�
		for (size_t i = 0; i < count; ++i)
		{
			CGameObject* pLoadedObject = LoadGameObject(File);
			pLayer->AddObject(pLoadedObject, false);
		}
	}

	fclose(File);

	return pNewLevel;
}

CGameObject* CPortalScript::LoadGameObject(FILE* _File)
{
	CGameObject* pObject = new CGameObject;

	// GameObject �� �̸� �ε�
	wstring Name;
	LoadWString(Name, _File);
	pObject->SetName(Name);

	// Component ���� �ε�
	COMPONENT_TYPE Type = COMPONENT_TYPE::END;
	while (true)
	{
		// ����Ǿ��ִ� ������ � ������Ʈ���� Ȯ��
		fread(&Type, sizeof(COMPONENT_TYPE), 1, _File);

		// ���� Ÿ�� ������ END �� ���, ����� ������Ʈ ������ ���̴�.
		if (COMPONENT_TYPE::END == Type)
			break;

		// ����� Ÿ�Կ� �´� ������Ʈ�� ���� ��Ű��, �����Ҷ��� ������ ������ �����͸� �д´�.
		CComponent* pComponent = GetComponent(Type);

		// ������ ������Ʈ�� ������Ʈ�� �־��ش�.
		pObject->AddComponent(pComponent);

		// �������� ������ �о�ͼ� �����Ѵ�.
		pComponent->LoadFromFile(_File);
	}

	// Script ���� �ε�	
	size_t ScriptCount = 0;
	fread(&ScriptCount, sizeof(size_t), 1, _File);

	for (size_t i = 0; i < ScriptCount; ++i)
	{
		// Script �� �̸� �б�
		wstring ScriptName;
		LoadWString(ScriptName, _File);

		// ���� Script �̸����� �̸��� �ش��ϴ� Script ����
		CScript* pScript = CScriptMgr::GetScript(ScriptName);


		pScript->LoadFromFile(_File);

		pObject->AddComponent(pScript);
	}

	// Child ���� �ε�
	size_t ChildCount = 0;
	fread(&ChildCount, sizeof(size_t), 1, _File);

	for (size_t i = 0; i < ChildCount; ++i)
	{
		CGameObject* pChildObject = LoadGameObject(_File);
		pObject->AddChild(pChildObject);
	}

	return pObject;
}

CComponent* CPortalScript::GetComponent(COMPONENT_TYPE _Type)
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


void CPortalScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider)
{
}

void CPortalScript::Overlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider)
{
	if (CLevelMgr::GetInst()->GetCurrentLevel()->GetName() == L"Home")
	{
		if (KEY_TAP(KEY::F))
		{
			wstring levelName = L"Ice";
			wstring StrLevelLoadPath = CPathMgr::GetInst()->GetContentPath();
			StrLevelLoadPath += (L"level\\" + levelName + L".lv");
			CLevel* pLevel = LoadLevel(StrLevelLoadPath);

			//CCollisionMgr::GetInst()->CollisionCheck(1, 3); // Platform vs Player
			//CCollisionMgr::GetInst()->CollisionCheck(1, 4); // Platform vs Monster
			//CCollisionMgr::GetInst()->CollisionCheck(1, 6); // Platform vs Monster Projectile
			//CCollisionMgr::GetInst()->CollisionCheck(1, 5); // Platform vs Player Projectile

			//CCollisionMgr::GetInst()->CollisionCheck(5, 4); // Player Projectile vs Monster
			//CCollisionMgr::GetInst()->CollisionCheck(6, 3); // Monster Projectile vs player
			//CCollisionMgr::GetInst()->CollisionCheck(7, 3); // Object vs player

			ChangeLevel(pLevel, LEVEL_STATE::PLAY);
		}
		
	}
	if (CLevelMgr::GetInst()->GetCurrentLevel()->GetName() == L"Ice")
	{
		if (KEY_TAP(KEY::F))
		{
			wstring levelName = L"Boss";
			wstring StrLevelLoadPath = CPathMgr::GetInst()->GetContentPath();
			StrLevelLoadPath += (L"level\\" + levelName + L".lv");
			CLevel* pLevel = LoadLevel(StrLevelLoadPath);

			ChangeLevel(pLevel, LEVEL_STATE::PLAY);
		}
	}
}

void CPortalScript::SaveToFile(FILE* _File)
{
}

void CPortalScript::LoadFromFile(FILE* _File)
{
}


