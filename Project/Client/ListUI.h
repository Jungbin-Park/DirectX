#pragma once
#include "EditorUI.h"

class ListUI :
    public EditorUI
{
private:
    vector<string>  m_vecList;

public:
    virtual void Update() override;

public:
    ListUI();
    ~ListUI();
};

