#pragma once
#include "TE_Sub.h"

#include <Engine/CTileMap.h>

class TE_Viewer :
    public TE_Sub
{
private:
    CTileMap* m_Tile;


public:
    CTileMap* GetTileMap() { return m_Tile; }

private:
    void DrawTile();


public:
    virtual void Init() override;
    virtual void Update() override;

public:
    TE_Viewer();
    ~TE_Viewer();
};

