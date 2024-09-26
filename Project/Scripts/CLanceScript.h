#pragma once
#include <Engine/CScript.h>

class CLanceScript :
    public CScript
{
private:
    Ptr<CPrefab>    m_SparkPref;

    CGameObject*    m_Boss;
    float           m_Speed;
    Vec3            m_Dir;

    bool            m_bRotate;
    bool            m_bShoot;
    bool            m_BCountStart;
    bool            m_bHit;
    float           m_ShootInitTime;
    float           m_ShootTime;

    float           m_Angle;
    float           m_Dist;
    

public:
    void ShootLance();


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

