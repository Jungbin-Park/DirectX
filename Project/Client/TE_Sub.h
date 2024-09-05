#pragma once
#include "EditorUI.h"

#include "TileMapEditor.h"
#include <Engine/CAssetMgr.h>

class TE_Sub :
    public EditorUI
{
private:
    TileMapEditor* m_Owner;

public:
    TileMapEditor* GetOwner() { return m_Owner; }
    class TE_Viewer* GetTEViewer() { return m_Owner->GetTEViewer(); }
    class TE_Detail* GetTEDetail() { return m_Owner->GetTEDetail(); }

public:
    TE_Sub();
    ~TE_Sub();

    friend class TileMapEditor;
};

