#pragma once
#include "CComponent.h"

class CRenderComponent :
    public CComponent
{
private:
    CMesh*              m_Mesh;
    CGraphicShader*     m_Shader;

public:
    void SetMesh(CMesh* _Mesh) { m_Mesh = _Mesh; }
    void SetShader(CGraphicShader* _Shader) { m_Shader = _Shader; }

    CMesh* GetMesh() { return m_Mesh; }
    CGraphicShader* GetShader() { return m_Shader; }

public:
    virtual void FinalTick() = 0;
    virtual void Render() = 0;
    virtual CRenderComponent* Clone() = 0;
public:
    CRenderComponent(COMPONENT_TYPE _Type);
    ~CRenderComponent();
};

