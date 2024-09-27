#pragma once

#include <Engine/CScript.h>

class CCameraMoveScript :
    public CScript
{
private:
    float           m_CamSpeed;
    bool            m_BossSpawn;
    float           m_Timer;
    Vec3            m_Dir;

    CGameObject*    m_FollowObj;

public:
    void BossSpawn();

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

