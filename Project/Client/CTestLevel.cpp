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
#include <Scripts/CHitSparkScript.h>
#include <Scripts/CPortalScript.h>
#include <Scripts/CTeleportScript.h>
#include <Scripts/CFireDragonScript.h>
#include <Scripts/CFireBallScript.h>



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

	pLevel->SetName(L"Test");

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
		pPlayer->AddComponent(new CFSM);

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


		// FireDragon
		/*CGameObject* pFD = new CGameObject;
		pFD->SetName(L"FireDragon");

		pFD->AddComponent(new CTransform);
		pFD->AddComponent(new CMeshRender);
		pFD->AddComponent(new CCollider2D);
		pFD->AddComponent(new CFlipBookComponent);
		pFD->AddComponent(new CFireDragonScript);

		pFD->Transform()->SetRelativeScale(100.f, 70.f, 0.f);

		pFD->Collider2D()->SetIndependentScale(false);
		pFD->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
		pFD->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));

		pFD->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
		pFD->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));

		pLevel->AddObject(5, pFD);*/

		// 포탈
		/*CGameObject* pPortal = new CGameObject;
		pPortal->SetName(L"Portal");

		pPortal->AddComponent(new CTransform);
		pPortal->AddComponent(new CMeshRender);
		pPortal->AddComponent(new CCollider2D);
		pPortal->AddComponent(new CFlipBookComponent);
		pPortal->AddComponent(new CPortalScript);

		pPortal->Transform()->SetRelativeScale(200.f, 150.f, 0.f);

		pPortal->Collider2D()->SetIndependentScale(false);
		pPortal->Collider2D()->SetOffset(Vec3(0.0f, 0.8f, 0.f));
		pPortal->Collider2D()->SetScale(Vec3(0.5f, 0.1f, 0.f));

		pPortal->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
		pPortal->MeshRender()->SetMaterial(CAssetMgr::GetInst()->Load<CMaterial>(L"material\\WarpStone.mtrl", L"material\\WarpStone.mtrl"));

		pLevel->AddObject(7, pPortal);*/

		// 텔포 이펙트
		/*CGameObject* TeleportEffect = new CGameObject;
		TeleportEffect->SetName(L"TeleportEffect");

		TeleportEffect->AddComponent(new CTransform);
		TeleportEffect->AddComponent(new CMeshRender);
		TeleportEffect->AddComponent(new CFlipBookComponent);
		TeleportEffect->AddComponent(new CTeleportScript);

		TeleportEffect->Transform()->SetRelativePos(0.f, 300.f, 0.f);
		TeleportEffect->Transform()->SetRelativeScale(170.f, 750.f, 0.f);

		TeleportEffect->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
		TeleportEffect->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));

		pLevel->AddObject(0, TeleportEffect);*/

		// 보스
		/*CGameObject* pBoss = new CGameObject;
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

		pLevel->AddObject(4, pBoss);*/

		/*CGameObject* pFD = new CGameObject;
		pFD->SetName(L"FireDragon");
		
		pFD->AddComponent(new CTransform);
		pFD->AddComponent(new CMeshRender);
		pFD->AddComponent(new CCollider2D);
		pFD->AddComponent(new CFlipBookComponent);
		pFD->AddComponent(new CFireDragonScript);
		
		pFD->Transform()->SetRelativeScale(100.f, 100.f, 0.f);
		
		pFD->Collider2D()->SetIndependentScale(false);
		pFD->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
		pFD->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
		
		pFD->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
		pFD->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));

		pLevel->AddObject(5, pFD);*/

		

		// HitSpark
		/*CGameObject* pHit = new CGameObject;
		pHit->SetName(L"HitSpark");

		pHit->AddComponent(new CTransform);
		pHit->AddComponent(new CMeshRender);
		pHit->AddComponent(new CFlipBookComponent);
		pHit->AddComponent(new CHitSparkScript);

		pHit->Transform()->SetRelativeScale(100.f, 100.f, 0.f);

		pHit->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
		pHit->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));
		
		pLevel->AddObject(1, pHit);*/

		// IceSword
		/*CGameObject* pSword = new CGameObject;
		pSword->SetName(L"IceSword");
		
		pSword->AddComponent(new CTransform);
		pSword->AddComponent(new CMeshRender);
		pSword->AddComponent(new CCollider2D);
		pSword->AddComponent(new CFlipBookComponent);
		pSword->AddComponent(new CBSlashScript);
		
		pSword->Transform()->SetRelativeScale(100.f, 300.f, 0.f);
		
		pSword->Collider2D()->SetIndependentScale(false);
		pSword->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
		pSword->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
		
		pSword->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
		pSword->MeshRender()->SetMaterial(pMtrl);

		pLevel->AddObject(6, pSword);*/

		// Lance
		/*CGameObject* pLance = new CGameObject;
		pLance->SetName(L"IceLance");

		pLance->AddComponent(new CTransform);
		pLance->AddComponent(new CMeshRender);
		pLance->AddComponent(new CCollider2D);
		pLance->AddComponent(new CFlipBookComponent);
		pLance->AddComponent(new CLanceScript);
		
		pLance->Transform()->SetRelativeScale(30.f, 150.f, 0.f);

		pLance->Collider2D()->SetIndependentScale(false);
		pLance->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
		pLance->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));

		pLance->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
		pLance->MeshRender()->SetMaterial(pMtrl);

		pLevel->AddObject(6, pLance);*/

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
		/*CGameObject* pArchWay = new CGameObject;
		pArchWay->SetName(L"ArchWay");
		pArchWay->AddComponent(new CTransform);
		pArchWay->AddComponent(new CMeshRender);

		pArchWay->Transform()->SetRelativePos(Vec3(0.f, 310.f, 100.f));
		pArchWay->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 0.f));

		pArchWay->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
		pArchWay->MeshRender()->SetMaterial(CAssetMgr::GetInst()->Load<CMaterial>(L"material\\ArchWay.mtrl", L"material\\ArchWay.mtrl"));

		pLevel->AddObject(2, pArchWay);*/

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
		pTileMapObj->SetName(L"Home");

		wstring strContentPath = CPathMgr::GetInst()->GetContentPath();
		CTileMap* pTile = new CTileMap;
		pTileMapObj->AddComponent(new CTransform);
		pTileMapObj->AddComponent(pTile);

		pTile->Load(strContentPath + L"tilemap\\home.tile");
		pTileMapObj->Transform()->SetRelativePos(Vec3(-880.f, 1800.f, 500.f));

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
	CCollisionMgr::GetInst()->CollisionCheck(1, 3); // Platform vs Player
	CCollisionMgr::GetInst()->CollisionCheck(1, 4); // Platform vs Monster
	CCollisionMgr::GetInst()->CollisionCheck(1, 6); // Platform vs Monster Projectile
	CCollisionMgr::GetInst()->CollisionCheck(1, 5); // Platform vs Player Projectile

	CCollisionMgr::GetInst()->CollisionCheck(5, 4); // Player Projectile vs Monster
	CCollisionMgr::GetInst()->CollisionCheck(6, 3); // Monster Projectile vs player
	CCollisionMgr::GetInst()->CollisionCheck(7, 3); // Object vs player


}

void CTestLevel::CreatePrefab()
{
	/*CGameObject* pFD = new CGameObject;
	pFD->SetName(L"FireDragon");

	pFD->AddComponent(new CTransform);
	pFD->AddComponent(new CMeshRender);
	pFD->AddComponent(new CCollider2D);
	pFD->AddComponent(new CFlipBookComponent);
	pFD->AddComponent(new CFireDragonScript);

	pFD->Transform()->SetRelativeScale(100.f, 70.f, 0.f);

	pFD->Collider2D()->SetIndependentScale(false);
	pFD->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pFD->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));

	pFD->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pFD->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));

	Ptr<CPrefab> pPrefab = new CPrefab;
	pPrefab->SetProtoObject(pFD);

	CAssetMgr::GetInst()->AddAsset<CPrefab>(L"FireDragonPref", pPrefab);

	wstring FilePath = CPathMgr::GetInst()->GetContentPath();
	FilePath += L"prefab\\FireDragon.pref";
	pPrefab->Save(FilePath);*/
	

	/*CTileMap* pTile = new CTileMap;
	pTile->SetName(L"map1");*/

}

void CTestLevel::LevelInit()
{

}
