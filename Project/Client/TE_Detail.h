#pragma once
#include "TE_Sub.h"

class TE_Detail :
    public TE_Sub
{
private:
    Ptr<CTexture>   m_AtlasTex;
    Ptr<CTexture>   m_SelectedTile;
    ImVec2          m_AtlasTileSize;
    ImVec2          m_CanvasSize;
    ImVec2          m_CurImageSize;

    ImVec2          ImageRectMin;
    ImVec2          m_MousePos;

    float           m_Ratio;

    bool            m_PopupActive;

private:
    void TileInfo();
    void SaveTile();
    void SelectCheck();

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

