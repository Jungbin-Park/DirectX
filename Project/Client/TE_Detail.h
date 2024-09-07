#pragma once
#include "TE_Sub.h"

#include <Engine/CTileMap.h>

class TE_Detail :
    public TE_Sub
{
private:
    Ptr<CTexture>   m_AtlasTex;         // 아틀라스 이미지
    Ptr<CTexture>   m_SelectedTile;     // 선택된 타일

    ImVec2          m_AtlasTileSize;    // Tile 하나 사이즈
    ImVec2          m_ClickedRectLT;    // 선택된 타일 좌표 LT
    ImVec2          m_ClickedRectRB;    // 선택된 타일 좌표 RB

    ImVec2          m_CanvasSize;       // Atlas 그릴 캔버스 최대 사이즈
    ImVec2          m_CurImageSize;     // Ratio 적용된 현재 아틀라스 이미지 전체 사이즈

    ImVec2          ImageRectMin;       // Image 위젯 좌상단 좌표(윈도우 좌표 기준)
    ImVec2          m_MousePos;         // 현재 마우스 위치(윈도우 좌표 기준)

    float           m_Ratio;

    bool            m_PopupActive;
    bool            m_bDrawRect;

private:
    void TileInfo();
    void SelectCheck();
    void TileSetting();
    void SaveTile();

public:
    void SetAtlasTex(Ptr<CTexture> _Tex) { m_AtlasTex = _Tex; }
    void SetAtlasTileSize(ImVec2 _TileSize) { m_AtlasTileSize = _TileSize; }

public:
    virtual void Init() override;
    virtual void Update() override;

private:
    void SelectTexture(DWORD_PTR _ListUI);

public:
    TE_Detail();
    ~TE_Detail();
};

