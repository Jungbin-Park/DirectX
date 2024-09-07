#include "pch.h"
#include "TE_Detail.h"

#include "CEditorMgr.h"

#include "ListUI.h"
#include "TreeUI.h"
#include "TE_Viewer.h"

#include <Engine/CSprite.h>


TE_Detail::TE_Detail()
	: m_AtlasTex(nullptr)
	, m_CanvasSize(ImVec2(400.f, 400.f))
	, m_CurImageSize(ImVec2(0.f, 0.f))
	, m_SelectedTile(nullptr)
	, m_AtlasTileSize(ImVec2(0.f, 0.f))
	, m_ClickedRectLT(ImVec2(0.f, 0.f))
	, m_ClickedRectRB(ImVec2(0.f, 0.f))
	, ImageRectMin(ImVec2(0.f, 0.f))
	, m_MousePos(ImVec2(0.f, 0.f))
	, m_Ratio(0.f)	
	, m_PopupActive(false)
	, m_bDrawRect(false)
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
	// 타일 정보
	TileInfo();

	// 타일 선택
	SelectCheck();

	// 타일 설정
	TileSetting();

	if (m_PopupActive)
		SaveTile();
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
	// Ratio 적용된 이미지 사이즈
	m_CurImageSize = ImVec2(width * m_Ratio, height * m_Ratio);

	ImGui::Image(m_AtlasTex->GetSRV().Get(), m_CurImageSize
		, uv_min, uv_max, tint_col, border_col);
}

void TE_Detail::SelectCheck()
{
	// Image 위젯 좌상단 좌표(윈도우 좌표 기준)
	ImageRectMin = ImGui::GetItemRectMin();

	// 현재 마우스 위치(윈도우 좌표 기준)
	m_MousePos = ImGui::GetMousePos();

	// 텍스쳐 내에서의 마우스 좌표
	ImVec2 vDiff = ImVec2(m_MousePos.x - ImageRectMin.x, m_MousePos.y - ImageRectMin.y);

	int idxX = floor(vDiff.x / (m_AtlasTileSize.x * m_Ratio));
	int idxY = floor(vDiff.y / (m_AtlasTileSize.y * m_Ratio));

	ImVec2 RectLT = ImVec2(ImageRectMin.x + idxX * m_AtlasTileSize.x * m_Ratio,
		ImageRectMin.y + idxY * m_AtlasTileSize.y * m_Ratio);
	ImVec2 RectRB = ImVec2(RectLT.x + m_AtlasTileSize.x * m_Ratio,
		RectLT.y + m_AtlasTileSize.y * m_Ratio);
	
	// 마우스 좌표를 따라다니는 사각형 그리기
	if(0 < vDiff.x && vDiff.x < m_CurImageSize.x 
		&& 0 < vDiff.y && vDiff.y < m_CurImageSize.y)
	ImGui::GetWindowDrawList()->AddRect(RectLT, RectRB, ImGui::GetColorU32(ImVec4(1.f, 1.f, 0.f, 1.f)), 0.f, 0.f, 2.f);

	ImVec2 vRowCol = ImVec2(m_AtlasTex->Height() / m_AtlasTileSize.y, m_AtlasTex->Width() / m_AtlasTileSize.x);

	// 클릭된 지점에 그리는 사각형 그리기
	if (ImGui::IsItemClicked())
	{
		m_bDrawRect = true;

		m_ClickedRectLT = RectLT;
		m_ClickedRectRB = RectRB;

		float clickedIdx = idxX + (idxY * vRowCol.y);

		// 인덱스만 넘겨주면 됨
		GetOwner()->GetTEViewer()->SetAtlasTexture(m_AtlasTex);
		GetOwner()->GetTEViewer()->SetClickedIdx(clickedIdx);
	}

	if (m_bDrawRect)
	{
		ImGui::GetWindowDrawList()->AddRect(m_ClickedRectLT, m_ClickedRectRB, ImGui::GetColorU32(ImVec4(1.f, 0.f, 0.f, 1.f)), 0.f, 0.f, 2.f);
	}

	// 마우스 위치의 아틀라스 픽셀좌표	
	float PixelPos[] = { vDiff.x, vDiff.y };
	ImGui::InputFloat2("PixelPos", PixelPos);
}

void TE_Detail::TileSetting()
{
	ImVec2 resolution = ImVec2(m_AtlasTex->Width(), m_AtlasTex->Height());
	float arrResolution[]{ resolution.x, resolution.y };
	ImGui::InputFloat2("AtlasResolution", arrResolution, "%.3f", ImGuiInputTextFlags_::ImGuiInputTextFlags_ReadOnly);

	// 타일 row, col 세팅
	Vec2 vRowCol = GetOwner()->GetTile()->GetRowCol();
	float arrRowCol[] = { vRowCol.x, vRowCol.y };
	if (ImGui::InputFloat2("RowCol", arrRowCol))
	{
		GetOwner()->GetTile()->SetRowCol(arrRowCol[0], arrRowCol[1]);
	}

	
	// 아틀라스 타일 size
	Vec2 vAtlasTileSize = Vec2(m_AtlasTileSize.x, m_AtlasTileSize.y);
	float AtlasTileSize[] = { vAtlasTileSize.x, vAtlasTileSize.y };
	if (ImGui::InputFloat2("AtlasTileSize", AtlasTileSize))
	{
		SetAtlasTileSize(ImVec2(AtlasTileSize[0], AtlasTileSize[1]));
		GetOwner()->GetTile()->SetAtlasTileSize(Vec2(AtlasTileSize[0], AtlasTileSize[1]));
	}

	// 아틀라스 이미지 선택
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

	if (ImGui::Button("Save TileMap", ImVec2(100.f, 18.f)))
	{
		m_PopupActive = true;
	}
}

void TE_Detail::SaveTile()
{
	ImGui::OpenPopup("Save TileMap");

	if (ImGui::BeginPopupModal("Save TileMap", NULL, 0))
	{
		ImGui::Text("Enter TileMap Name");
		ImGui::Text("");
		static char cBuff[50] = {};
		ImGui::InputText("##SaveName", cBuff, sizeof(cBuff));
		ImGui::Text("");

		if (ImGui::Button("Save", ImVec2(120, 0)))
		{
			m_PopupActive = false;

			std::wstring wsBuff = std::wstring(cBuff, cBuff + strlen(cBuff));
			GetOwner()->GetTEViewer()->Save(wsBuff);

			ImGui::CloseCurrentPopup();
		}

		ImGui::SetItemDefaultFocus();
		ImGui::SameLine();
		if (ImGui::Button("Cancel", ImVec2(120, 0)))
		{
			m_PopupActive = false;
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
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
	GetOwner()->GetTile()->SetAtlasTexture(pTex);
}
