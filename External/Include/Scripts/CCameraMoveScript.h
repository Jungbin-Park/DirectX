#pragma once

#include <Engine/CScript.h>

class CCameraMoveScript :
    public CScript
{
private:
    float           m_CamSpeed;

    CGameObject*    m_FollowObj;

public:
    virtual void Begin() override;
    virtual void Tick() override;
    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
private:
    void OrthoGraphicMove();
    void PerspectiveMove();


public:
    CLONE(CCameraMoveScript);
    CCameraMoveScript();
    ~CCameraMoveScript();
};

