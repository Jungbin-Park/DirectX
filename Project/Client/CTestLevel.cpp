#include "pch.h"
#include "CTestLevel.h"

#include <Engine/CAssetMgr.h>
#include <Engine/assets.h>

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CLayer.h>
#include <Engine/CGameObject.h>
#include <Engine/components.h>
#include <Engine/CState.h>

#include <Engine/CCollisionMgr.h>

#include <Scripts/CPlayerScript.h>
#include <Scripts/CSlashScript.h>
#include <Scripts/CCameraMoveScript.h>
#include <Scripts/CMarkerScript.h>
#include <Scripts/CursorScript.h>
#include <Scripts/CGhoulScript.h>
#include <Scripts/CPlatformScript.h>
#include <Scripts/CManagerScript.h>
#include <Scripts/CBossScript.h>
#include <Scripts/CCrystalScript.h>
#include <Scripts/CWaterScript.h>
#include <Scripts/CBSlashScript.h>
#include <Scripts/CLanceScript.h>

#include<States/CIdleState.h>

#include <Engine/CSetColorCS.h>
#include <Engine/CStructuredBuffer.h>

#include "CLevelSaveLoad.h"


void CTestLevel::CreateTestLevel()
{
	// Material
	Ptr<CMaterial> pMtrl = CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl");
	Ptr<CMaterial> pmMtrl = CAssetMgr::GetInst()->Load<CMaterial>(L"material\\std2d.mtrl", L"material\\std2d.mtrl");
	Ptr<CMaterial> pCursorMtrl = CAssetMgr::GetInst()->Load<CMaterial>(L"material\\Cursor.mtrl", L"material\\Cursor.mtrl");
	Ptr<CMaterial> pGateVMtrl = CAssetMgr::GetInst()->Load<CMaterial>(L"material\\GateVertical.mtrl", L"material\\GateVertical.mtrl");
	Ptr<CMaterial> pGateHMtrl = CAssetMgr::GetInst()->Load<CMaterial>(L"material\\GateHorizontal.mtrl", L"material\\GateHorizontal.mtrl");
	Ptr<CMaterial> pAlphaBlendMtrl = CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DAlphaBlendMtrl");
	Ptr<CMaterial> pDebugShapeMtrl = CAssetMgr::GetInst()->FindAsset<CMaterial>(L"DebugShapeMtrl");

	//pmMtrl->SetTexParam(TEX_0, CAssetMgr::GetInst()->FindAsset<CTexture>(L"PlayerMarker.png"));
	//Ptr<CTexture> pTexture = CAssetMgr::GetInst()->FindAsset<CTexture>(L"texture//Character.png");
	//pAlphaBlendMtrl->SetTexParam(TEX_0, pTexture);

	CreatePrefab();

	// 컴퓨트 쉐이더 테스트용 텍스쳐 생성
	Ptr<CTexture> pTestTex = CAssetMgr::GetInst()->CreateTexture(L"ComputeShaderTestTex"
		, 1026, 1026, DXGI_FORMAT_R8G8B8A8_UNORM
		, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS);

	CSetColorCS cs;
	cs.SetTargetTexture(pTestTex);
	cs.SetClearColor(Vec4(0.f, 1.f, 0.f, 1.f));
	cs.Execute();
	pMtrl->SetTexParam(TEX_0, pTestTex);

	CStructuredBuffer* pBuffer = new CStructuredBuffer;
	pBuffer->Create(sizeof(tParticle), 1, SB_TYPE::SRV_UAV, true);

	tParticle Particle = {};
	tParticle Particle2 = {};

	Particle.Active = true;
	Particle.vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	pBuffer->SetData(&Particle);

	pBuffer->GetData(&Particle2);
	delete pBuffer;

	// Level 생성
	CLevel* pLevel = new CLevel;

	pLevel->SetName(L"Boss");

	//// 레벨 지정

	pLevel->GetLayer(0)->SetName(L"Default");
	pLevel->GetLayer(1)->SetName(L"Background");
	pLevel->GetLayer(2)->SetName(L"Tile");
	pLevel->GetLayer(3)->SetName(L"Player");
	pLevel->GetLayer(4)->SetName(L"Monster");
	pLevel->GetLayer(5)->SetName(L"PlayerProjectile");
	pLevel->GetLayer(6)->SetName(L"MonsterProjectile");
	pLevel->GetLayer(7)->SetName(L"Object");
	pLevel->GetLayer(10)->SetName(L"UI");

	// 오브젝트 추가
	{
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

		// 게임 매니저 오브젝트
		pObject = new CGameObject;
		pObject->SetName(L"GameManager");
		pObject->AddComponent(new CManagerScript);

		pLevel->AddObject(0, pObject);


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
		pCursor->MeshRender()->SetMaterial(pCursorMtrl);

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
		pPlayer->Collider2D()->SetScale(Vec3(0.5f, 0.7f, 1.f));

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

		// 보스
		CGameObject* pBoss = new CGameObject;
		pBoss->SetName(L"Boss");

		pBoss->AddComponent(new CTransform);
		pBoss->AddComponent(new CMeshRender);
		pBoss->AddComponent(new CCollider2D);
		pBoss->AddComponent(new CFlipBookComponent);
		pBoss->AddComponent(new CBossScript);
		pBoss->AddComponent(new CFSM);

		pBoss->Transform()->SetRelativePos(0.f, 200.f, 100.f);
		pBoss->Transform()->SetRelativeScale(150.f, 150.f, 1.f);
		
		pBoss->Collider2D()->SetIndependentScale(false);
		pBoss->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
		pBoss->Collider2D()->SetScale(Vec3(0.5f, 0.7f, 1.f));
		
		pBoss->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
		pBoss->MeshRender()->SetMaterial(pMtrl);

		pLevel->AddObject(4, pBoss);

		// Water
		/*CGameObject* pWater = new CGameObject;
		pWater->SetName(L"WaterBall");

		pWater->AddComponent(new CTransform);
		pWater->AddComponent(new CMeshRender);
		pWater->AddComponent(new CCollider2D);
		pWater->AddComponent(new CFlipBookComponent);
		pWater->AddComponent(new CWaterScript);

		pWater->Transform()->SetRelativeScale(100.f, 100.f, 0.f);

		pWater->Collider2D()->SetIndependentScale(false);
		pWater->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
		pWater->Collider2D()->SetScale(Vec3(0.3f, 0.3f, 1.f));

		pWater->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
		pWater->MeshRender()->SetMaterial(CAssetMgr::GetInst()->Load<CMaterial>(L"material\\WaterBall.mtrl", L"material\\WaterBall.mtrl"));

		pLevel->AddObject(6, pWater);*/

		// Crystal
		/*CGameObject* pCrystal = new CGameObject;
		pCrystal->SetName(L"Crystal");

		pCrystal->AddComponent(new CTransform);
		pCrystal->AddComponent(new CMeshRender);
		pCrystal->AddComponent(new CFlipBookComponent);
		pCrystal->AddComponent(new CCrystalScript);

		pCrystal->Transform()->SetRelativeScale(200.f, 200.f, 1.f);
		pCrystal->Transform()->SetRelativePos(0.f, 300.f, 1.f);

		pCrystal->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
		pCrystal->MeshRender()->SetMaterial(CAssetMgr::GetInst()->Load<CMaterial>(L"material\\Crystal.mtrl", L"material\\Crystal.mtrl"));

		pLevel->AddObject(7, pCrystal);*/


		// ArchWay
		CGameObject* pArchWay = new CGameObject;
		pArchWay->SetName(L"ArchWay");
		pArchWay->AddComponent(new CTransform);
		pArchWay->AddComponent(new CMeshRender);

		pArchWay->Transform()->SetRelativePos(Vec3(0.f, 310.f, 100.f));
		pArchWay->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 0.f));

		pArchWay->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
		pArchWay->MeshRender()->SetMaterial(CAssetMgr::GetInst()->Load<CMaterial>(L"material\\ArchWay.mtrl", L"material\\ArchWay.mtrl"));

		pLevel->AddObject(2, pArchWay);

		// 게이트 수평
		/*CGameObject* pProto = new CGameObject;
		pProto->SetName(L"GateHorizontal");
		pProto->AddComponent(new CTransform);
		pProto->AddComponent(new CMeshRender);

		pProto->Transform()->SetRelativePos(10.f, 470.f, 100.f);
		pProto->Transform()->SetRelativeScale(200.f, 200.f, 1.f);

		pProto->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
		pProto->MeshRender()->SetMaterial(pGateHMtrl);

		CGameObject* pPlatform = new CGameObject;
		pPlatform->SetName(L"Platform");
		pPlatform->AddComponent(new CTransform);
		pPlatform->AddComponent(new CCollider2D);
		pPlatform->AddComponent(new CPlatformScript);
		pPlatform->Transform()->SetRelativePos(0.f, 0.f, 100.f);
		pPlatform->Transform()->SetRelativeScale(100.f, 100.f, 1.f);

		pPlatform->Collider2D()->SetIndependentScale(true);
		pPlatform->Collider2D()->SetOffset(Vec3(0.f, 45.f, 0.f));
		pPlatform->Collider2D()->SetScale(Vec3(200.f, 100.f, 1.f));
		
		pProto->AddChild(pPlatform);

		pLevel->AddObject(2, pProto);*/

		// 게이트 수직
		/*pProto = new CGameObject;
		pProto->SetName(L"GateVertical");
		pProto->AddComponent(new CTransform);
		pProto->AddComponent(new CMeshRender);

		pProto->Transform()->SetRelativePos(-390.f, 20.f, 100.f);
		pProto->Transform()->SetRelativeScale(50.f, 320.f, 1.f);

		pProto->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
		pProto->MeshRender()->SetMaterial(pGateVMtrl);

		pPlatform = new CGameObject;
		pPlatform->SetName(L"Platform");
		pPlatform->AddComponent(new CTransform);
		pPlatform->AddComponent(new CCollider2D);
		pPlatform->AddComponent(new CPlatformScript);
		pPlatform->Transform()->SetRelativePos(0.f, 0.f, 100.f);
		pPlatform->Transform()->SetRelativeScale(100.f, 100.f, 1.f);

		pPlatform->Collider2D()->SetIndependentScale(true);
		pPlatform->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
		pPlatform->Collider2D()->SetScale(Vec3(35.f, 325.f, 1.f));

		pProto->AddChild(pPlatform);

		pLevel->AddObject(2, pProto);*/

		
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
		pMonster->SetName(L"Ghoul");

		pMonster->AddComponent(new CTransform);
		pMonster->AddComponent(new CMeshRender);
		pMonster->AddComponent(new CCollider2D);
		pMonster->AddComponent(new CFlipBookComponent);
		pMonster->AddComponent(new CGhoulScript);
		pMonster->AddComponent(new CFSM);

		pMonster->Transform()->SetRelativePos(300.f, 0.f, 100.f);
		pMonster->Transform()->SetRelativeScale(150.f, 150.f, 1.f);

		pMonster->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
		pMonster->Collider2D()->SetScale(Vec3(0.7, 0.7f, 1.f));

		pMonster->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
		pMonster->MeshRender()->SetMaterial(pMtrl);

		

		pLevel->AddObject(4, pMonster);*/

		// TileMap Object
		CGameObject* pTileMapObj = new CGameObject;
		pTileMapObj->SetName(L"IceTile");

		wstring strContentPath = CPathMgr::GetInst()->GetContentPath();
		CTileMap* pTile = new CTileMap;
		pTileMapObj->AddComponent(new CTransform);
		pTileMapObj->AddComponent(pTile);

		pTile->Load(strContentPath + L"tilemap\\IceBoss.tile");
		pTileMapObj->Transform()->SetRelativePos(Vec3(-1570.f, 2830.f, 500.f));

		pLevel->AddObject(2, pTileMapObj);

		// Particle Object
		/*CGameObject* pParticleObj = new CGameObject;
		pParticleObj->SetName(L"Particle");

		pParticleObj->AddComponent(new CTransform);
		pParticleObj->AddComponent(new CParticleSystem);

		pParticleObj->Transform()->SetRelativePos(Vec3(0.f, 0.f, 0.f));

		pLevel->AddObject(0, pParticleObj);*/

		/*pTileMapObj->TileMap()->SetRowCol(5, 5);
		pTileMapObj->TileMap()->SetTileSize(Vec2(64.f, 64.f));

		Ptr<CTexture> pTileAtlas = CAssetMgr::GetInst()->FindAsset<CTexture>(L"texture\\TILE.bmp");
		pTileMapObj->TileMap()->SetAtlasTexture(pTileAtlas);
		pTileMapObj->TileMap()->SetAtlasTileSize(Vec2(128.f, 128.f));

		pTile->Save(strContentPath + L"tilemap\\test1.tile");*/

		// PostProcess Object
		/*CGameObject* pGrayFilterObj = new CGameObject;
		pGrayFilterObj->SetName(L"GrayFilter");
		pGrayFilterObj->AddComponent(new CTransform);
		pGrayFilterObj->AddComponent(new CMeshRender);

		pGrayFilterObj->Transform()->SetRelativeScale(150.f, 150.f, 1.f);

		pGrayFilterObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
		pGrayFilterObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"DistortionMtrl"));

		pLevel->AddObject(0, pGrayFilterObj);*/
	}

	ChangeLevel(pLevel, LEVEL_STATE::STOP);

	// 충돌 지정
	CCollisionMgr::GetInst()->CollisionCheck(1, 4); // platform vs Monster
	CCollisionMgr::GetInst()->CollisionCheck(5, 4); // Player Projectile vs Monster
	CCollisionMgr::GetInst()->CollisionCheck(1, 3); // platform vs player;
	CCollisionMgr::GetInst()->CollisionCheck(5, 1); // Player Projectile vs platform
	CCollisionMgr::GetInst()->CollisionCheck(6, 1); // Monster Projectile vs platform

}

void CTestLevel::CreatePrefab()
{
	/*CGameObject* pWater = new CGameObject;
	pWater->SetName(L"WaterBall");

	pWater->AddComponent(new CTransform);
	pWater->AddComponent(new CMeshRender);
	pWater->AddComponent(new CCollider2D);
	pWater->AddComponent(new CFlipBookComponent);
	pWater->AddComponent(new CWaterScript);

	pWater->Transform()->SetRelativeScale(100.f, 100.f, 0.f);

	pWater->Collider2D()->SetIndependentScale(false);
	pWater->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pWater->Collider2D()->SetScale(Vec3(0.3f, 0.3f, 1.f));

	pWater->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pWater->MeshRender()->SetMaterial(CAssetMgr::GetInst()->Load<CMaterial>(L"material\\WaterBall.mtrl", L"material\\WaterBall.mtrl"));

	Ptr<CPrefab> pPrefab = new CPrefab;
	pPrefab->SetProtoObject(pWater);

	CAssetMgr::GetInst()->AddAsset<CPrefab>(L"WaterBallPref", pPrefab);

	wstring FilePath = CPathMgr::GetInst()->GetContentPath();
	FilePath += L"prefab\\WaterBall.pref";
	pPrefab->Save(FilePath);*/

	/*CTileMap* pTile = new CTileMap;
	pTile->SetName(L"map1");*/

}

void CTestLevel::LevelInit()
{

}
