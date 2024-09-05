#pragma once
#include "ComponentUI.h"

class TileMapUI :
    public ComponentUI
{
private:
    virtual void Update() override;

public:
    TileMapUI();
    ~TileMapUI();
};

