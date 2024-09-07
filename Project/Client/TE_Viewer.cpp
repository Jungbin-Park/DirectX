#include "pch.h"
#include "TE_Viewer.h"

#include <Engine/CTileMap.h>
#include <Engine/CTileMap.h>

TE_Viewer::TE_Viewer()
	: m_Tile(nullptr)
    , m_ClickedIdx(-1)
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

    Ptr<CTexture> tileAtlas = m_Tile->GetAtlasTexture();                                                // 아틀라스 텍스처
    ImVec2 tilesize = ImVec2(m_Tile->GetTileSize().x, m_Tile->GetTileSize().y);                         // 타일 사이즈
    vector<tTileInfo> tileInfo = m_Tile->GetTileInfo();                                                 // 타일 정보
    ImVec2 atlasTileSize = ImVec2(m_Tile->GetAtlasTileSize().x, m_Tile->GetAtlasTileSize().y);          // 아틀라스 타일 크기
    ImVec2 atlasResolution = ImVec2(m_Tile->GetAtlasResolution().x, m_Tile->GetAtlasResolution().y);    // 아틀라스 원본 해상도

    int row = m_Tile->GetRowCol().x;
    int col = m_Tile->GetRowCol().y;
    int atlasRow = m_Tile->GetAtlasMaxRow();
    int atlasCol = m_Tile->GetAtlasMaxCol();

    // 기존 타일 정보 그리기
    for (int r = 0; r < row; ++r)
    {
        for (int c = 0; c < col; ++c)
        {
            // ==============
            //    아틀라스
            // ==============
            // 인덱스(1차원)
            int Idx = tileInfo[(r * col) + c].ImgIdx;

            // 구조체의 인덱스를 받아와 아틀라스의 인덱스 x,y 구하기
            int IdxX = Idx % atlasCol;
            int IdxY = (Idx - IdxX) / atlasCol;

            ImVec2 tileLT = ImVec2(IdxX * atlasTileSize.x, IdxY * atlasTileSize.y);
            ImVec2 tileRB = ImVec2(tileLT.x + atlasTileSize.x, tileLT.y + atlasTileSize.y);

            // UV 좌표 계산
            ImVec2 uv_min = ImVec2(tileLT.x / atlasResolution.x, tileLT.y / atlasResolution.y);
            ImVec2 uv_max = ImVec2((tileLT.x + atlasTileSize.x) / atlasResolution.x, (tileLT.y + atlasTileSize.y) / atlasResolution.y);

            ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
            ImVec4 border_col = ImVec4(0.7f, 0.7f, 0.7f, 1.0f);

            // ==============
            //      타일 
            // ==============
            // 타일 위치 및 크기 설정
            ImVec2 tilePos(c * tilesize.x, r * tilesize.y + 20.f);

            // ImGui에 타일을 그리기
            ImGui::SetCursorPos(tilePos);
            ImGui::Image(tileAtlas->GetSRV().Get(), tilesize, uv_min, uv_max);

            // 마우스로 타일 클릭 시 처리
            if (ImGui::IsItemClicked())
            {
                // 넘겨 받은 idx 정보로 변경
                m_Tile->SetTileInfo((r * col) + c, m_ClickedIdx);
            }
        }
    }
}

void TE_Viewer::Save(const wstring& _Name)
{
    wstring strContentPath = CPathMgr::GetInst()->GetContentPath();
    m_Tile->Save(strContentPath + L"tilemap\\" + _Name + L".tile");
}
