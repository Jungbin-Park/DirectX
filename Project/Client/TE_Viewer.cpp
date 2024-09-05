#include "pch.h"
#include "TE_Viewer.h"

#include <Engine/CTileMap.h>

TE_Viewer::TE_Viewer()
	: m_Tile(nullptr)
{
}

TE_Viewer::~TE_Viewer()
{
}

void TE_Viewer::Init()
{
}

void TE_Viewer::Update()
{
    m_Tile = GetOwner()->GetTile();

    DrawTile();
}

void TE_Viewer::DrawTile()
{
    if (m_Tile == nullptr)
        return;

    int row = m_Tile->GetRowCol().x;
    int col = m_Tile->GetRowCol().y;
    ImVec2 tilesize = ImVec2(m_Tile->GetTileSize().x, m_Tile->GetTileSize().y);

    Ptr<CTexture> tileAtlas = m_Tile->GetAtlasTexture();  // 타일 아틀라스 텍스처
    ImVec2 atlasTileSize = ImVec2(m_Tile->GetAtlasTileSize().x, m_Tile->GetAtlasTileSize().y); // 아틀라스 내 타일 크기
    ImVec2 atlasResolution = ImVec2(m_Tile->GetAtlasResolution().x, m_Tile->GetAtlasResolution().y); // 아틀라스 텍스처 해상도

    ImVec2 tileLT = ImVec2(0.f, 0.f);
    ImVec2 tileRB = ImVec2(64.f, 64.f);

    for (int r = 0; r < row; ++r)
    {
        for (int c = 0; c < col; ++c)
        {
            // UV 좌표 계산
            ImVec2 uv_min = ImVec2(tileLT.x / atlasResolution.x, tileLT.y / atlasResolution.y);
            ImVec2 uv_max = ImVec2((tileLT.x + tilesize.x) / atlasResolution.x, (tileLT.y + tilesize.y) / atlasResolution.y);

            ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
            ImVec4 border_col = ImVec4(0.7f, 0.7f, 0.7f, 1.0f);

            // 타일 위치 및 크기 설정
            ImVec2 tilePos(c * tilesize.x, r * tilesize.y + 20.f);

            // ImGui에 타일을 그리기
            ImGui::SetCursorPos(tilePos);
            ImGui::Image(tileAtlas->GetSRV().Get(), tilesize, uv_min, uv_max);

            // 마우스로 타일 클릭 시 처리
            if (ImGui::IsItemClicked())
            {
                int a = 0;
                // 타일을 클릭했을 때의 처리 (예: 타일 선택)
                // 현재 선택된 타일을 변경하거나 편집할 수 있음
                //HandleTileClick(r, c);
            }
        }
    }
}
