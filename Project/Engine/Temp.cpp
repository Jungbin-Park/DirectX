#include "pch.h"
#include "Temp.h"

#include "CDevice.h"
#include "CPathMgr.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CAssetMgr.h"

#include "CEntity.h"
#include "CMesh.h"
#include "CConstBuffer.h"
#include "CGraphicShader.h"

tTransform g_ObjTrans = {};

int TempInit()
{
	// 크기 배율 설정
	g_ObjTrans.Scale = Vec4(0.5f, 0.5f, 0.5f, 1.f);

	return S_OK;
}

void TempTick()
{
	float dt = CTimeMgr::GetInst()->GetDeltaTime();

	if (CKeyMgr::GetInst()->GetKeyState(KEY::LEFT) == KEY_STATE::PRESSED)
	{
		g_ObjTrans.Pos.x -= dt * 1.f;
	}

	if (CKeyMgr::GetInst()->GetKeyState(KEY::RIGHT) == KEY_STATE::PRESSED)
	{
		g_ObjTrans.Pos.x += dt * 1.f;
	}

	if (CKeyMgr::GetInst()->GetKeyState(KEY::UP) == KEY_STATE::PRESSED)
	{
		g_ObjTrans.Pos.y += dt * 1.f;
	}

	if (CKeyMgr::GetInst()->GetKeyState(KEY::DOWN) == KEY_STATE::PRESSED)
	{
		g_ObjTrans.Pos.y -= dt * 1.f;
	}

	CConstBuffer* pTransformCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::TRANSFORM);
	pTransformCB->SetData(&g_ObjTrans);
}

void TempRender()
{
	// 랜더링 파이프라인 시작 전 옵션 설정

	CConstBuffer* pTransformCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::TRANSFORM);
	pTransformCB->Binding();

	CMesh* pRectMesh = CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh");
	CGraphicShader* pShader = CAssetMgr::GetInst()->FindAsset<CGraphicShader>(L"TestShader");

	pShader->Binding();
	pRectMesh->render();
}

void TempRelease()
{

}
