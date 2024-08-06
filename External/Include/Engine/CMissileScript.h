#pragma once
#include "CScript.h"

class CMissileScript :
    public CScript
{
private:
    float   m_Speed;


public:
    virtual void Tick() override;

public:
    CLONE(CMissileScript);
    CMissileScript();
    ~CMissileScript();
};

