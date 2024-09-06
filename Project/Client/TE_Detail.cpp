#include "pch.h"
#include "TE_Detail.h"

#include "CEditorMgr.h"

#include "ListUI.h"
#include "TreeUI.h"

#include <Engine/CSprite.h>


TE_Detail::TE_Detail()
	: m_AtlasTex(nullptr)
	, m_PopupActive(false)
	, m_CanvasSize(ImVec2(400.f, 400.f))
{
}

TE_Detail::~TE_Detail()
{
}

void TE_Detail::Init()
{
}

void TE_Detail::Update()
{
	TileInfo();

	
}

void TE_Detail::TileInfo()
{
	// 해상도
	UINT width = 0;
	UINT height = 0;

	if (nullptr != m_AtlasTex)
	{
		width = m_AtlasTex->Width();
		height = m_AtlasTex->Height();
	}

	// Tile Image
	ImVec2 uv_min = ImVec2(0.f, 0.f);
	ImVec2 uv_max = ImVec2(1.f, 1.f);

	ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	ImVec4 border_col = ImVec4(0.7f, 0.7f, 0.7f, 1.0f);

	m_Ratio = m_CanvasSize.x / width;
	m_CurImageSize = ImVec2(width * m_Ratio, height * m_Ratio);

	ImGui::Image(m_AtlasTex->GetSRV().Get(), m_CurImageSize
		, uv_min, uv_max, tint_col, border_col);

	

	SelectCheck();

	if (ImGui::Button("##TileTexBtn", ImVec2(18.f, 18.f)))
	{
		ListUI* pListUI = (ListUI*)CEditorMgr::GetInst()->FindEditorUI("List");
		pListUI->SetName("TileTexture");
		vector<string> vecTexNames;
		CAssetMgr::GetInst()->GetAssetNames(ASSET_TYPE::TEXTURE, vecTexNames);
		pListUI->AddList(vecTexNames);
		pListUI->AddDelegate(this, (DELEGATE_1)&TE_Detail::SelectTexture);
		pListUI->SetActive(true);
	}

	

	// 타일 row, col 세팅
	// 타일 size 세팅


	if (ImGui::Button("Save Sprite", ImVec2(100.f, 18.f)))
	{
		m_PopupActive = true;
	}

	ImGui::Separator();
}

void TE_Detail::SaveTile()
{

}

void TE_Detail::SelectCheck()
{
	// Image 위젯 좌상단 좌표(윈도우 좌표 기준)
	ImageRectMin = ImGui::GetItemRectMin();

	// 현재 마우스 위치(윈도우 좌표 기준)
	m_MousePos = ImGui::GetMousePos();

	// 텍스쳐 내에서의 마우스 좌표
	ImVec2 vDiff = ImVec2(m_MousePos.x - ImageRectMin.x, m_MousePos.y - ImageRectMin.y);

	if (ImGui::IsItemClicked())
	{
		int idxX = floor(vDiff.x / (m_AtlasTileSize.x * m_Ratio));
		int idxY = floor(vDiff.y / (m_AtlasTileSize.y * m_Ratio));

			
		// 타일을 클릭했을 때의 처리 (예: 타일 선택)
		// 현재 선택된 타일을 변경하거나 편집할 수 있음
		//HandleTileClick(r, c);
	}

	// 아틀라스 타일 size
	float AtlasTileSize[] = { m_AtlasTileSize.x, m_AtlasTileSize.y };
	ImGui::InputFloat2("AtlasTileSize", AtlasTileSize);

	// 마우스 위치의 아틀라스 픽셀좌표	
	float PixelPos[] = { vDiff.x, vDiff.y };
	ImGui::InputFloat2("PixelPos", PixelPos);

}

void TE_Detail::SelectTexture(DWORD_PTR _ListUI)
{
	ListUI* pListUI = (ListUI*)_ListUI;
	string strName = pListUI->GetSelectName();

	if (strName == "None")
	{
		m_AtlasTex = nullptr;
		return;
	}

	wstring strAssetName = wstring(strName.begin(), strName.end());

	Ptr<CTexture> pTex = CAssetMgr::GetInst()->FindAsset<CTexture>(strAssetName);

	assert(pTex.Get());

	m_AtlasTex = pTex;

}
