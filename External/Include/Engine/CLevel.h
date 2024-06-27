#pragma once
#include "CEntity.h"

class CLayer;
class CGameObject;

class CLevel :
    public CEntity
{
private:
    CLayer* m_Layer[MAX_LAYER];

public:
    void AddObject(int LayerIdx, CGameObject* _Object);

public:
    void Begin();
    void Tick();
    void FinalTick();
    void Render();

public:
    virtual CLevel* Clone() { return new CLevel(*this); }
    CLevel();
    ~CLevel();
};

