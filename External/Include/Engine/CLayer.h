#pragma once
#include "CEntity.h"

class CGameObject;

class CLayer :
    public CEntity
{
private:
    vector<CGameObject*>    m_Parents;
    int                     m_LayerIdx;

public:
    int GetLayerIdx() { return m_LayerIdx; }
    void AddObject(CGameObject* _Object) { m_Parents.push_back(_Object); }
    const vector<CGameObject*>& GetParentObjects() { return m_Parents; }

public:
    void Begin();
    void Tick();
    void FinalTick();

public:
    virtual CLayer* Clone() { return new CLayer(*this); }
    CLayer(int _LayerIdx);
    ~CLayer();
};

