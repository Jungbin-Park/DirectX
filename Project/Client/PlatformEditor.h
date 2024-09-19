#pragma once
#include "EditorUI.h"

class PlatformEditor :
    public EditorUI
{
private:


private:


public:
    virtual void Init() override;
    virtual void Update() override;

    virtual void Activate() override;
    virtual void Deactivate() override;

public:
    PlatformEditor();
    ~PlatformEditor();
};

