#include "pch.h"
#include "CAssetMgr.h"

#include "assets.h"

CAssetMgr::CAssetMgr()
{

}

CAssetMgr::~CAssetMgr()
{
	for (UINT i = 0; i < (UINT)ASSET_TYPE::END; ++i)
	{
		Delete_Map(m_mapAsset[i]);
	}
}

void CAssetMgr::Init()
{
	CMesh* pMesh = nullptr;
	
	// RectMesh 생성
	// 0 -- 1
	// |    |
	// 3 -- 2
	Vtx arrVtx[4] = {};

	arrVtx[0].vPos = Vec3(-0.5f, 0.5f, 0.f);
	arrVtx[0].vColor = Vec4(1.f, 0.f, 0.f, 1.f);

	arrVtx[1].vPos = Vec3(0.5f, 0.5f, 0.f);
	arrVtx[1].vColor = Vec4(0.f, 1.f, 0.f, 1.f);

	arrVtx[2].vPos = Vec3(0.5f, -0.5f, 0.f);
	arrVtx[2].vColor = Vec4(0.f, 0.f, 1.f, 1.f);

	arrVtx[3].vPos = Vec3(-0.5f, -0.5f, 0.f);
	arrVtx[3].vColor = Vec4(1.f, 1.f, 1.f, 1.f);


	// Index 버퍼 생성
	UINT arrIdx[6] = {};
	arrIdx[0] = 0;	arrIdx[1] = 1;	arrIdx[2] = 2;
	arrIdx[3] = 0; 	arrIdx[4] = 2;	arrIdx[5] = 3;

	pMesh = new CMesh;
	pMesh->Create(arrVtx, 4, arrIdx, 6);
	

	CGraphicShader* pShader = nullptr;
	pShader = new CGraphicShader;
	pShader->CreateVertexShader(L"shader\\test.fx", "VS_Test");
	pShader->CreatePixelShader(L"shader\\test.fx", "PS_Test");

}

CAsset* CAssetMgr::FindAsset(ASSET_TYPE _Type, const wstring& _Key)
{
	map<wstring, CAsset*>::iterator iter = m_mapAsset[(UINT)_Type].find(_Key);

	if (iter == m_mapAsset[(UINT)_Type].end())
	{
		return nullptr;
	}

	return iter->second;
}

//void CAssetMgr::AddAsset(const wstring& _strName, CAsset* _Asset)
//{
//	ASSET_TYPE Type = _Asset->GetAssetType();
//
//	assert(!FindAsset(Type, _strName));
//
//	m_mapAsset[(UINT)Type].insert(make_pair(_strName, _Asset));
//}
