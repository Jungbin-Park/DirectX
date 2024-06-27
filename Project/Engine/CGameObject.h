#pragma once
#include "CEntity.h"

class CComponent;
class CRenderComponent;

#define GET_COMPONENT(Type, TYPE) class C##Type* Type() {return (C##Type*)GetComponent(COMPONENT_TYPE::TYPE);}

class CGameObject :
    public CEntity
{
private:
    CComponent* m_arrCom[(UINT)COMPONENT_TYPE::END];
    CRenderComponent* m_RenderCom;

public:
    void AddComponent(CComponent* _Component);
    CComponent* GetComponent(COMPONENT_TYPE _Type) { return m_arrCom[(UINT)_Type]; }

    GET_COMPONENT(Transform, TRANSFORM);
    GET_COMPONENT(MeshRender, MESHRENDER);

public:
    void Begin();
    void Tick();
    void FinalTick();
    void Render();

public:
    virtual CGameObject* Clone() { return new CGameObject(*this); }
    CGameObject();
    ~CGameObject();
};

