#pragma once
#include <Engine/CScript.h>

class CLanceScript :
    public CScript
{
private:
    CGameObject*    m_Boss;

    bool            m_bRotate;

    float           m_Angle;
    float           m_Dist;


public:
    virtual void Begin() override;
    virtual void Tick() override;

    virtual void BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider) override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;

public:
    CLONE(CLanceScript);
    CLanceScript();
    ~CLanceScript();
};

