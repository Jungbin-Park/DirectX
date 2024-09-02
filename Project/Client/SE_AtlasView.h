#pragma once
#include "SE_Sub.h"

class SE_AtlasView :
    public SE_Sub
{
public:
    virtual void Init() override;
    virtual void Update() override;

public:
    SE_AtlasView();
    ~SE_AtlasView();
};
