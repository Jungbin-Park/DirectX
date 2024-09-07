#include "pch.h"
#include "TileMapUI.h"

#include <Engine/CTileMap.h>
#include "CEditorMgr.h"
#include "TileMapEditor.h"
#include "TE_Detail.h"
#include "TE_Viewer.h"

#include "TreeUI.h"

TileMapUI::TileMapUI()
	: ComponentUI(COMPONENT_TYPE::TILEMAP)
{

}

TileMapUI::~TileMapUI()
{
}

void TileMapUI::Update()
{
	Title();

	CTileMap* pTile = GetTargetObject()->TileMap();
	assert(pTile);

	Vec2 vRowCol = pTile->GetRowCol();
	Vec2 vTileSize = pTile->GetTileSize();
	Ptr<CTexture> pAtlasTex = pTile->GetAtlasTexture();
	Vec2 vAtlasTileSize = pTile->GetAtlasTileSize();

	// 현재 타일 정보
	float arrRowCol[] = { vRowCol.x, vRowCol.y };
	ImGui::InputFloat2("RowCol", arrRowCol);

	float arrTileSize[]{ vTileSize.x, vTileSize.y };
	ImGui::InputFloat2("TileSize", arrTileSize);

	float arrAtlasTileSize[]{ vAtlasTileSize.x, vAtlasTileSize.y };
	ImGui::InputFloat2("AtlasTileSize", arrAtlasTileSize);

	if (arrRowCol[0] < 0) arrRowCol[0] = 0;
	if (arrRowCol[1] < 0) arrRowCol[1] = 0;

	if (arrTileSize[0] <= 0) arrTileSize[0] = 1;
	if (arrTileSize[1] <= 0) arrTileSize[1] = 1;

	if (arrAtlasTileSize[0] <= 0) arrAtlasTileSize[0] = 1;
	if (arrAtlasTileSize[1] <= 0) arrAtlasTileSize[1] = 1;
	
	// 값 타일 맵 적용
	pTile->SetRowCol(arrRowCol[0], arrRowCol[1]);
	pTile->SetTileSize(Vec2(arrTileSize[0], arrTileSize[1]));
	pTile->SetAtlasTileSize(Vec2(arrAtlasTileSize[0], arrAtlasTileSize[1]));


	// 타일 맵 변경
	/*string tileName;
	tileName = string(pTile->GetName().begin(), pTile->GetName().end());

	ImGui::Text("TileMap");
	ImGui::SameLine(120);
	ImGui::SetNextItemWidth(150.f);
	ImGui::InputText("##TileMap", (char*)tileName.c_str(), ImGuiInputTextFlags_::ImGuiInputTextFlags_ReadOnly);

	if (ImGui::BeginDragDropTarget())
	{
		const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ContentTree");
		if (payload)
		{
			TreeNode** ppNode = (TreeNode**)payload->Data;
			TreeNode* pNode = *ppNode;

			Ptr<CAsset> pAsset = (CAsset*)pNode->GetData();
			if (ASSET_TYPE::PREFAB == pAsset->GetAssetType())
			{
				SetTileMap((CPrefab*)pAsset.Get());
			}
		}

		ImGui::EndDragDropTarget();
	}

	ImGui::SameLine();
	if (ImGui::Button("##AtlasTexBtn", ImVec2(18.f, 18.f)))
	{
		ListUI* pListUI = (ListUI*)CEditorMgr::GetInst()->FindEditorUI("List");
		pListUI->SetName("Texture");
		vector<string> vecTexNames;
		CAssetMgr::GetInst()->GetAssetNames(ASSET_TYPE::TEXTURE, vecTexNames);
		pListUI->AddList(vecTexNames);
		pListUI->AddDelegate(this, (DELEGATE_1)&SE_Detail::SelectTexture);
		pListUI->SetActive(true);
	}*/


	// 에디터
	if (ImGui::Button("TileMap Editor", ImVec2(100.f, 20.f)))
	{
		TileMapEditor* pTileMapEditor = (TileMapEditor*)CEditorMgr::GetInst()->FindEditorUI("1TileMapEditor");
		if (pTileMapEditor != nullptr)
		{
			pTileMapEditor->SetTargetTile(pTile);
			Ptr<CTexture> tileTex = pTile->GetAtlasTexture();
			pTileMapEditor->GetTEDetail()->SetAtlasTex(tileTex);
			pTileMapEditor->GetTEDetail()->SetAtlasTileSize(ImVec2(arrAtlasTileSize[0], arrAtlasTileSize[1]));
			pTileMapEditor->SetActive(true);
		}
	}
}
