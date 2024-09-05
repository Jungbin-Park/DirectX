#pragma once
#include "TE_Sub.h"

class TE_Detail :
    public TE_Sub
{


public:
    virtual void Init() override;
    virtual void Update() override;

public:
    TE_Detail();
    ~TE_Detail();
};

