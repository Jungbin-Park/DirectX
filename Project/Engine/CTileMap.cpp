#include "pch.h"
#include "CTileMap.h"

#include "CTransform.h"
#include "CAssetMgr.h"

#include "CStructuredBuffer.h"

CTileMap::CTileMap()
	: CRenderComponent(COMPONENT_TYPE::TILEMAP)
	, m_Row(1)
	, m_Col(1)
	, m_AtlasMaxRow(0)
	, m_AtlasMaxCol(0)
	, m_Buffer(nullptr)
{
	SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"TileMapMtrl"));

	m_Buffer = new CStructuredBuffer;
}

CTileMap::CTileMap(const CTileMap& _Origin)
	: CRenderComponent(_Origin)
	, m_Row(_Origin.m_Row)
	, m_Col(_Origin.m_Col)
	, m_TileSize(_Origin.m_TileSize)
	, m_TileAtlas(_Origin.m_TileAtlas)
	, m_AtlasResolution(_Origin.m_AtlasResolution)
	, m_AtlasTileSize(_Origin.m_AtlasTileSize)
	, m_AtlasTileSliceUV(_Origin.m_AtlasTileSliceUV)
	, m_AtlasMaxRow(_Origin.m_AtlasMaxRow)
	, m_AtlasMaxCol(_Origin.m_AtlasMaxCol)
	, m_vecTileInfo(_Origin.m_vecTileInfo)
	, m_Buffer(nullptr)
{
	m_Buffer = new CStructuredBuffer;
}

CTileMap::~CTileMap()
{
	delete m_Buffer;
}

void CTileMap::Init()
{
	// 행, 렬 설정해서 구조화버퍼 크기 조정
	SetRowCol(m_Row, m_Col);
}

void CTileMap::FinalTick()
{
}

void CTileMap::Render()
{
	// 타일의 정보를 구조화버퍼를 통해서 t 레지스터에 바인딩 시킨다.
	m_Buffer->SetData(m_vecTileInfo.data(), sizeof(tTileInfo) * m_Row * m_Col);
	m_Buffer->Binding(15);

	GetMaterial()->SetTexParam(TEX_0, m_TileAtlas);
	GetMaterial()->SetScalarParam(INT_1, m_AtlasMaxRow);
	GetMaterial()->SetScalarParam(INT_2, m_AtlasMaxCol);
	GetMaterial()->SetScalarParam(VEC2_1, Vec2(m_Col, m_Row));
	GetMaterial()->SetScalarParam(VEC2_0, m_AtlasTileSliceUV);
	GetMaterial()->Binding();
	Transform()->Binding();
	GetMesh()->Render();
}

void CTileMap::SetRowCol(UINT _Row, UINT _Col)
{
	m_Row = _Row;
	m_Col = _Col;

	ChangeTileMapSize();

	// 타일 개수
	UINT TileCount = m_Row * m_Col;

	// 타일 정보를 저장하는 벡터의 데이터 개수가 타일 개수랑 다르면 리사이즈
	if (m_vecTileInfo.size() < TileCount)
	{
		m_vecTileInfo.clear();
		m_vecTileInfo.resize(TileCount);
	}

	// 타일정보를 전달받아서 t 레지스터에 전달시킬 구조화버퍼가 타일 전체 데이터 사이즈보다 작으면 리사이즈
	if (m_Buffer->GetElementSize() < TileCount)
	{
		m_Buffer->Create(sizeof(tTileInfo), TileCount, SB_TYPE::SRV_ONLY, false);
	}
}

void CTileMap::SetTileSize(Vec2 _Size)
{
	m_TileSize = _Size;

	ChangeTileMapSize();
}

void CTileMap::ChangeTileMapSize()
{
	Vec2 vSize = m_TileSize * Vec2((float)m_Col, (float)m_Row);
	Transform()->SetRelativeScale(vSize.x, vSize.y, 1.f);
}

void CTileMap::SetAtlasTexture(Ptr<CTexture> _Atlas)
{
	m_TileAtlas = _Atlas;

	if (nullptr == m_TileAtlas)
		m_AtlasResolution = Vec2(0.f, 0.f);
	else
		m_AtlasResolution = Vec2((float)_Atlas->Width(), (float)_Atlas->Height());

	SetAtlasTileSize(m_AtlasTileSize);
}

void CTileMap::SetAtlasTileSize(Vec2 _TileSize)
{
	m_AtlasTileSize = _TileSize;

	if (nullptr != m_TileAtlas)
	{
		m_AtlasTileSliceUV = m_AtlasTileSize / m_AtlasResolution;

		m_AtlasMaxCol = int(m_AtlasResolution.x / m_AtlasTileSize.x);
		m_AtlasMaxRow = int(m_AtlasResolution.y / m_AtlasTileSize.y);
	}
}

void CTileMap::SaveToFile(FILE* _File)
{
	SaveDataToFile(_File);

	fwrite(&m_Col, sizeof(int), 1, _File);
	fwrite(&m_Row, sizeof(int), 1, _File);

	fwrite(&m_TileSize, sizeof(Vec2), 1, _File);
	fwrite(&m_AtlasTileSize, sizeof(Vec2), 1, _File);

	for (size_t i = 0; i < m_vecTileInfo.size(); ++i)
	{
		fwrite(&m_vecTileInfo[i], sizeof(tTileInfo), 1, _File);
	}

	// 아틀라스 텍스쳐
	SaveAssetRef(m_TileAtlas, _File);
}

void CTileMap::LoadFromFile(FILE* _File)
{
	LoadDataFromFile(_File);

	fread(&m_Col, sizeof(int), 1, _File);
	fread(&m_Row, sizeof(int), 1, _File);

	SetRowCol(m_Row, m_Col);

	fread(&m_TileSize, sizeof(Vec2), 1, _File);
	fread(&m_AtlasTileSize, sizeof(Vec2), 1, _File);

	SetTileSize(m_TileSize);

	for (size_t i = 0; i < m_vecTileInfo.size(); ++i)
	{
		fread(&m_vecTileInfo[i], sizeof(tTileInfo), 1, _File);
	}

	// 아틀라스 텍스쳐
	LoadAssetRef(m_TileAtlas, _File);
	if (nullptr != m_TileAtlas)
	{
		SetAtlasTexture(m_TileAtlas);
	}
}

int CTileMap::Save(const wstring& _FilePath)
{
	FILE* File = nullptr;
	_wfopen_s(&File, _FilePath.c_str(), L"wb");

	if (nullptr == File)
		return E_FAIL;

	SaveToFile(File);

	fclose(File);

	return S_OK;
}

int CTileMap::Load(const wstring& _FilePath)
{
	FILE* File = nullptr;
	_wfopen_s(&File, _FilePath.c_str(), L"rb");

	if (nullptr == File)
		return E_FAIL;

	LoadFromFile(File);

	fclose(File);

	return S_OK;
}
