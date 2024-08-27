#pragma once
#include "EditorUI.h"

class Content :
    public EditorUI
{
private:
    class TreeUI*   m_Tree;

public:
    virtual void Update() override;

public:
    Content();
    ~Content();
};

