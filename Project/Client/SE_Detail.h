#pragma once
#include "SE_Sub.h"

class SE_Detail :
    public SE_Sub
{
public:
    virtual void Init() override;
    virtual void Update() override;

public:
    SE_Detail();
    ~SE_Detail();

};
