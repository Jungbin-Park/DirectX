#include "pch.h"
#include "CTestLevel.h"

#include <Engine/CAssetMgr.h>
#include <Engine/assets.h>

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CLayer.h>
#include <Engine/CGameObject.h>
#include <Engine/components.h>

#include <Engine/CCollisionMgr.h>

#include <Scripts/CPlayerScript.h>
#include <Scripts/CSlashScript.h>
#include <Scripts/CCameraMoveScript.h>
#include <Scripts/CMarkerScript.h>
#include <Scripts/CursorScript.h>

#include "CLevelSaveLoad.h"


void CTestLevel::CreateTestLevel()
{
	// Material
	Ptr<CMaterial> pMtrl = CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl");
	Ptr<CMaterial> pmMtrl = CAssetMgr::GetInst()->Load<CMaterial>(L"material\\std2d.mtrl", L"material\\std2d.mtrl");
	Ptr<CMaterial> pAlphaBlendMtrl = CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DAlphaBlendMtrl");
	Ptr<CMaterial> pDebugShapeMtrl = CAssetMgr::GetInst()->FindAsset<CMaterial>(L"DebugShapeMtrl");

	//pmMtrl->SetTexParam(TEX_0, CAssetMgr::GetInst()->FindAsset<CTexture>(L"PlayerMarker.png"));
	//Ptr<CTexture> pTexture = CAssetMgr::GetInst()->FindAsset<CTexture>(L"texture//Character.png");
	//pAlphaBlendMtrl->SetTexParam(TEX_0, pTexture);

	CreatePrefab();

	// Level 생성
	CLevel* pLevel = new CLevel;

	//// 레벨 지정
	//ChangeLevel(pLevel, LEVEL_STATE::PLAY);

	pLevel->GetLayer(0)->SetName(L"Default");
	pLevel->GetLayer(1)->SetName(L"Background");
	pLevel->GetLayer(2)->SetName(L"Tile");
	pLevel->GetLayer(3)->SetName(L"Player");
	pLevel->GetLayer(4)->SetName(L"Monster");
	pLevel->GetLayer(5)->SetName(L"PlayerProjectile");
	pLevel->GetLayer(6)->SetName(L"MonsterProjectile");
	pLevel->GetLayer(10)->SetName(L"UI");


	// 카메라 오브젝트
	CGameObject* CamObj = new CGameObject;
	CamObj->SetName(L"MainCamera");
	CamObj->AddComponent(new CTransform);
	CamObj->AddComponent(new CCamera);
	CamObj->AddComponent(new CCameraMoveScript);

	// 우선순위를 0 : MainCamera 로 설정
	CamObj->Camera()->SetPriority(0);

	// 카메라 레이어 설정 (31번 레이어 제외 모든 레이어를 촬영)
	CamObj->Camera()->SetLayerAll();
	CamObj->Camera()->SetLayer(31, false);
	CamObj->Camera()->SetFar(100000.f);
	CamObj->Camera()->SetProjType(ORTHOGRAPHIC);
	pLevel->AddObject(0, CamObj);

	CGameObject* pObject = nullptr;


	// 광원 오브젝트 추가
	pObject = new CGameObject;
	pObject->SetName(L"PointLight 1");
	pObject->AddComponent(new CTransform);
	pObject->AddComponent(new CLight2D);

	pObject->Light2D()->SetLightType(LIGHT_TYPE::DIRECTIONAL);
	pObject->Light2D()->SetLightColor(Vec3(1.f, 1.f, 1.f));
	pObject->Light2D()->SetRadius(2000.f);
	pObject->Transform()->SetRelativePos(Vec3(0.f, 0.f, 100.f));

	pLevel->AddObject(0, pObject);

	// 커서 오브젝트
	CGameObject* pCursor = new CGameObject;
	pCursor->SetName(L"Cursor");
	pCursor->AddComponent(new CTransform);
	pCursor->AddComponent(new CMeshRender);
	pCursor->AddComponent(new CursorScript);

	pCursor->Transform()->SetRelativeScale(100.f, 100.f, 1.f);

	pCursor->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));

	pLevel->AddObject(10, pCursor);
	

	// 플레이어 오브젝트
	CGameObject* pPlayer = new CGameObject;
	pPlayer->SetName(L"Player");
	pPlayer->AddComponent(new CTransform);
	pPlayer->AddComponent(new CMeshRender);
	pPlayer->AddComponent(new CCollider2D);
	pPlayer->AddComponent(new CFlipBookComponent);
	pPlayer->AddComponent(new CPlayerScript);
	pPlayer->Transform()->SetRelativePos(0.f, 0.f, 100.f);
	pPlayer->Transform()->SetRelativeScale(150.f, 150.f, 1.f);

	pPlayer->Collider2D()->SetIndependentScale(false);
	pPlayer->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pPlayer->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));

	pPlayer->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pPlayer->MeshRender()->SetMaterial(pMtrl);

	Ptr<CFlipBook> pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\idledown.flip");
	pPlayer->FlipBookComponent()->AddFlipBook(0, pFlipBook);
	pPlayer->FlipBookComponent()->Play(0, 10, true);

	// 화살표
	CGameObject* pMarker = new CGameObject;
	pMarker->SetName(L"pMarker");

	pMarker->AddComponent(new CTransform);
	pMarker->AddComponent(new CMeshRender);
	pMarker->AddComponent(new CMarkerScript);

	pMarker->Transform()->SetRelativePos(0.f, -0.3f, 0.f);
	pMarker->Transform()->SetRelativeScale(0.6f, 0.6f, 0.f);

	pMarker->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pMarker->MeshRender()->SetMaterial(pmMtrl);

	pPlayer->AddChild(pMarker);

	pLevel->AddObject(3, pPlayer);

	CamObj->Camera()->SetFollowObj(pPlayer);

	/*Ptr<CPrefab> pPrefab = new CPrefab;
	wstring FilePath = CPathMgr::GetInst()->GetContentPath();
	FilePath += L"prefab\\Player.pref";
	pPrefab->Load(FilePath);
	CGameObject* pPlayerPref = pPrefab->Instantiate();
	CreateObject(pPlayerPref, 3);*/


	// 프리팹화
	/*Ptr<CPrefab> pPrefab = new CPrefab;
	pPrefab->SetProtoObject(pPlayer);

	CAssetMgr::GetInst()->AddAsset<CPrefab>(L"PlayerPref", pPrefab);

	wstring FilePath = CPathMgr::GetInst()->GetContentPath();
	FilePath += L"prefab\\Player.pref";
	pPrefab->Save(FilePath);*/

	//CGameObject* pClonePlayer = pPlayer->Clone();


	// Monster Object
	/*CGameObject* pMonster = new CGameObject;
	pMonster->SetName(L"Monster");

	pMonster->AddComponent(new CTransform);
	pMonster->AddComponent(new CMeshRender);
	pMonster->AddComponent(new CCollider2D);

	pMonster->Transform()->SetRelativePos(-400.f, 0.f, 100.f);
	pMonster->Transform()->SetRelativeScale(150.f, 150.f, 1.f);	

	pMonster->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pMonster->Collider2D()->SetScale(Vec3(1.2f, 1.2f, 1.f));

	pMonster->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pMonster->MeshRender()->SetMaterial(pMtrl);

	pLevel->AddObject(4, pMonster);*/

	// TileMap Object
	CGameObject* pTileMapObj = new CGameObject;
	pTileMapObj->SetName(L"TileMap");

	wstring strContentPath = CPathMgr::GetInst()->GetContentPath();
	CTileMap* pTile = new CTileMap;
	pTileMapObj->AddComponent(new CTransform);
	pTileMapObj->AddComponent(pTile);

	pTile->Load(strContentPath + L"tilemap\\home.tile");
	pTileMapObj->Transform()->SetRelativePos(Vec3(-500.f, 250.f, 500.f));

	/*pTileMapObj->TileMap()->SetRowCol(5, 5);
	pTileMapObj->TileMap()->SetTileSize(Vec2(64.f, 64.f));

	Ptr<CTexture> pTileAtlas = CAssetMgr::GetInst()->FindAsset<CTexture>(L"texture\\TILE.bmp");
	pTileMapObj->TileMap()->SetAtlasTexture(pTileAtlas);
	pTileMapObj->TileMap()->SetAtlasTileSize(Vec2(128.f, 128.f));

	pTile->Save(strContentPath + L"tilemap\\test1.tile");*/

	pLevel->AddObject(2, pTileMapObj);


	// PostProcess Object
	/*CGameObject* pGrayFilterObj = new CGameObject;
	pGrayFilterObj->SetName(L"GrayFilter");
	pGrayFilterObj->AddComponent(new CTransform);
	pGrayFilterObj->AddComponent(new CMeshRender);

	pGrayFilterObj->Transform()->SetRelativeScale(150.f, 150.f, 1.f);

	pGrayFilterObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pGrayFilterObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"DistortionMtrl"));

	pLevel->AddObject(0, pGrayFilterObj);*/


	ChangeLevel(pLevel, LEVEL_STATE::STOP);

	// 충돌 지정
	CCollisionMgr::GetInst()->CollisionCheck(3, 4); // Player vs Monster
	CCollisionMgr::GetInst()->CollisionCheck(5, 4); // Player Projectile vs Monster

}

void CTestLevel::CreatePrefab()
{
	/*CGameObject* pProto = new CGameObject;
	pProto->SetName(L"Slash");
	pProto->AddComponent(new CTransform);
	pProto->AddComponent(new CMeshRender);
	pProto->AddComponent(new CSlashScript);

	pProto->Transform()->SetRelativeScale(100.f, 100.f, 1.f);

	pProto->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pProto->MeshRender()->SetMaterial(CAssetMgr::GetInst()->Load<CMaterial>(L"material\\Slash.mtrl", L"material\\Slash.mtrl"));

	Ptr<CPrefab> pPrefab = new CPrefab;
	pPrefab->SetProtoObject(pProto);

	CAssetMgr::GetInst()->AddAsset<CPrefab>(L"SlashPref", pPrefab);

	wstring FilePath = CPathMgr::GetInst()->GetContentPath();
	FilePath += L"prefab\\Slash.pref";
	pPrefab->Save(FilePath);*/

	/*CTileMap* pTile = new CTileMap;
	pTile->SetName(L"map1");*/

}
