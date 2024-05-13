#pragma once
#include "CEntity.h"

class CLayer;

class CLevel :
    public CEntity
{
private:
    CLayer* m_Layer[MAX_LAYER];

public:
    void Tick();
    void FinalTick();
    void Render();

public:
    virtual CLevel* Clone() { return new CLevel(*this); }
    CLevel();
    ~CLevel();
};

