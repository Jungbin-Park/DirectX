#pragma once
#include "TE_Sub.h"

#include <Engine/CTileMap.h>

class TE_Viewer :
    public TE_Sub
{
private:
    CTileMap*       m_Tile;

    Ptr<CTexture>   m_AtlasTex;         // Detail에서 전달받은 아틀라스 텍스쳐
    ImVec2          m_ClickedRectLT;    // 선택된 타일 좌표 LT
    ImVec2          m_ClickedRectRB;    // 선택된 타일 좌표 RB   

    float           m_AtlasIdx;
    float           m_ClickedIdx;       // 선택된 아틀라스 인덱스
    

public:
    CTileMap* GetTileMap() { return m_Tile; }

    void SetAtlasTexture(Ptr<CTexture> _Tex) { m_AtlasTex = _Tex; }
    void SetClickedRectLT(ImVec2 _ClickedLT) { m_ClickedRectLT = _ClickedLT; }
    void SetClickedRectRB(ImVec2 _ClickedRB) { m_ClickedRectRB = _ClickedRB; }
    void SetClickedIdx(float _Idx) { m_ClickedIdx = _Idx; }

    void Save(const wstring& _Name);

private:
    void DrawTile();


public:
    virtual void Init() override;
    virtual void Update() override;

private:
    

public:
    TE_Viewer();
    ~TE_Viewer();
};

