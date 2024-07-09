#pragma once
#include "CScript.h"

class CCameraMoveScript :
    public CScript
{
private:
    float   m_CamSpeed;

public:
    virtual void Tick() override;

public:
    CLONE(CCameraMoveScript);
    CCameraMoveScript();
    ~CCameraMoveScript();
};

