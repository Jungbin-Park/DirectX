#pragma once
#include <Engine/CScript.h>

class CWaterScript :
    public CScript
{
private:
    Ptr<CPrefab>    m_SparkPref;

    CGameObject*    m_Boss;

    bool            m_bRotate;
    bool            m_bShoot;
    bool            m_bHit;
    bool            m_bCountStart;

    float           m_Speed;
    Vec3            m_Dir;

    float           m_XPos;
    float           m_YPos;
    float           m_Angle;
    float           m_Dist;

    float           m_ShootInitTime;
    float           m_ShootWaterSpacing;

    float           m_rotationSpeed;

public:
    void ShootWater();

    void SetShootTime(float _Time); 
    

public:
    virtual void Begin() override;
    virtual void Tick() override;

    virtual void BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider) override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;

public:
    CLONE(CWaterScript);
    CWaterScript();
    ~CWaterScript();
};

