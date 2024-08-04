#pragma once
#include "CEntity.h"

class CComponent;
class CRenderComponent;
class CScript;

#define GET_COMPONENT(Type, TYPE) class C##Type* Type() { return (C##Type*)GetComponent(COMPONENT_TYPE::TYPE); }

class CGameObject :
    public CEntity
{
private:
    CComponent*             m_arrCom[(UINT)COMPONENT_TYPE::END];
    CRenderComponent*       m_RenderCom;
    vector<CScript*>        m_vecScript;

    CGameObject*            m_Parent;
    vector<CGameObject*>    m_vecChildren;

    int                     m_LayerIdx; // 소속 레이어의 인덱스 번호

public:
    void AddComponent(CComponent* _Component);
    CComponent* GetComponent(COMPONENT_TYPE _Type) { return m_arrCom[(UINT)_Type]; }
    CRenderComponent* GetRenderComponent() { return m_RenderCom; }

    CGameObject* GetParent() { return m_Parent; }
    int GetLayerIdx() { return m_LayerIdx; }
    void AddChild(CGameObject* _ChildObject);
    const vector<CGameObject*>& GetChildren() { return m_vecChildren; }

    void DisConnenctWithLayer();

    GET_COMPONENT(Transform, TRANSFORM);
    GET_COMPONENT(MeshRender, MESHRENDER);
    GET_COMPONENT(Camera, CAMERA);

public:
    void Begin();
    void Tick();
    void FinalTick();
    void Render();

public:
    virtual CGameObject* Clone() { return new CGameObject(*this); }
    CGameObject();
    ~CGameObject();

    friend class CLevel;
    friend class CLayer;
};

