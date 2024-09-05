#include "pch.h"
#include "TileMapUI.h"

#include <Engine/CTileMap.h>
#include "CEditorMgr.h"
#include "TileMapEditor.h"

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

	if (ImGui::Button("TileMap Editor", ImVec2(100.f, 20.f)))
	{
		TileMapEditor* pTileMapEditor = (TileMapEditor*)CEditorMgr::GetInst()->FindEditorUI("TileMapEditor");
		pTileMapEditor->SetTargetTile(pTile);
		pTileMapEditor->SetActive(true);
		
	}
}