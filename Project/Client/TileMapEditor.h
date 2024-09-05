#pragma once
#include "EditorUI.h"

#include <Engine/CTileMap.h>

class TE_Viewer;
class TE_Detail;

class TileMapEditor :
    public EditorUI
{
private:
    CTileMap*   m_TargetTile;

    TE_Viewer*  m_Viewer;
    TE_Detail*  m_Detail;

public:
    TE_Viewer* GetTEViewer() { return m_Viewer; }
    TE_Detail* GetTEDetail() { return m_Detail; }
    CTileMap* GetTile() { return m_TargetTile; }

    void SetTargetTile(CTileMap* _TargetTile) { m_TargetTile = _TargetTile; }

public:
    virtual void Init() override;
    virtual void Update() override;

    virtual void Activate() override;
    virtual void Deactivate() override;

public:
    TileMapEditor();
    ~TileMapEditor();
};

