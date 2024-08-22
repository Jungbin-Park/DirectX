#pragma once
#include "CScript.h"

class CCameraMoveScript :
    public CScript
{
private:
    float           m_CamSpeed;
    CGameObject*    m_FollowObj;

public:
    void SetFollowObj(CGameObject* _Obj) { m_FollowObj = _Obj; }

public:
    virtual void Tick() override;

private:
    void OrthoGraphicMove();
    void PerspectiveMove();

public:
    CLONE(CCameraMoveScript);
    CCameraMoveScript();
    ~CCameraMoveScript();
};

