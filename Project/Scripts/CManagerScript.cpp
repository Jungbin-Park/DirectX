#include "pch.h"
#include "CManagerScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CTimeMgr.h>
#include <Engine/CFSM.h>
#include <Engine/CState.h>
#include <Engine/assets.h>
#include <Engine/CFontMgr.h>
#include <Engine/CRenderMgr.h>
#include <Engine/CKeyMgr.h>
#include <Engine/CLayer.h>

#include <States/CStateMgr.h>

#include "CPlayerScript.h"

CManagerScript::CManagerScript()
	: CScript(SCRIPT_TYPE::MANAGERSCRIPT)
	, m_Score(0)
	, m_GateHPref(nullptr)
	, m_GateVPref(nullptr)
	, m_bGate(false)
	, m_Player(nullptr)
	, m_Boss(nullptr)
	, m_Logo{}
{
	SetName(L"ManagerScript");
}

CManagerScript::~CManagerScript()
{
}


void CManagerScript::Begin()
{
	SetName(L"ManagerScript");
	m_GateVPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\GateVertical.pref");
	m_GateHPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\GateHorizontal.pref");
	m_bBGM = true;
	m_CurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	swprintf_s(m_Logo, L"Press Any Key To Start");
}

void CManagerScript::Tick()
{
	m_Player = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Player");
	m_Boss = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Boss");
	CPlayerScript* pScript = nullptr;

	if (m_Score == 4)
		GateOpen();

	if (m_Player != nullptr)
	{
		pScript = (CPlayerScript*)m_Player->GetScriptByName(L"CPlayerScript");

		if (pScript->IsDead())
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

	// Level 별 동작
	if (m_CurLevel->GetName() == L"Title")
	{
		// Title Logo
		CRenderMgr::GetInst()->SetTitleLogo(true);

		// BGM
		if (m_bBGM)
		{
			if (m_BGM != nullptr)
			{
				m_BGM->Stop();
			}
			m_BGM = CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\Title.wav");
			m_BGM->Play(0, 1.f, false);
			m_bBGM = false;
		}

		// Level Change
		if (KEY_TAP(KEY::LBTN) || KEY_TAP(KEY::SPACE))
		{
			wstring levelName = L"Home";
			wstring StrLevelLoadPath = CPathMgr::GetInst()->GetContentPath();
			StrLevelLoadPath += (L"level\\" + levelName + L".lv");
			CLevel* pLevel = LoadLevel(StrLevelLoadPath);

			ChangeLevel(pLevel, LEVEL_STATE::PLAY);
		}

	}
	else if (m_CurLevel->GetName() == L"Home")
	{
		if (m_BGM != nullptr)
		{
			m_BGM->Stop();
		}

		CRenderMgr::GetInst()->SetTitleLogo(false);
		if (m_bBGM)
		{
			m_BGM = CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\Home.wav");
			m_BGM->Play(0, 1.f, false);
			m_bBGM = false;
		}
	}
	else if (m_CurLevel->GetName() == L"Ice")
	{
		if (m_BGM != nullptr)
		{
			m_BGM->Stop();
		}

		if (m_bBGM)
		{
			m_BGM = CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\Home.wav");
			m_BGM->Play(0, 1.f, false);
			m_bBGM = false;
		}
	}
	else if (m_CurLevel->GetName() == L"Boss")
	{
		if (m_BGM != nullptr)
		{
			m_BGM->Stop();
		}

		if (m_bBGM)
		{
			m_BGM = CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\Home.wav");
			m_BGM->Play(0, 1.f, false);
			m_bBGM = false;
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

CLevel* CManagerScript::LoadLevel(const wstring& _FilePath)
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

CGameObject* CManagerScript::LoadGameObject(FILE* _File)
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

CComponent* CManagerScript::GetComponent(COMPONENT_TYPE _Type)
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

void CManagerScript::SaveToFile(FILE* _File)
{
}

void CManagerScript::LoadFromFile(FILE* _File)
{
}


