#pragma once
#include "EditorUI.h"

class Inspector :
    public EditorUI
{
private:


public:
    virtual void Update() override;

public:
    Inspector();
    ~Inspector();
};

