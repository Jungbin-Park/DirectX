#pragma once
#include <Engine/CScript.h>

class CBSlashScript :
    public CScript
{
private:
    Ptr<CPrefab>    m_SparkPref;
    CGameObject*    m_Boss;

    bool            m_bSlash;

    float           m_Speed;
    Vec3            m_Dir;

    float           m_Angle;
    float           m_StartAngle;
    float           m_RotatedAngle;
    float           m_Dist;

    int             m_CurSlashCount;
    int             m_SlashCount;

public:
    void Slash();

public:
    virtual void Begin() override;
    virtual void Tick() override;

    virtual void BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider) override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;

public:
    CLONE(CBSlashScript);
    CBSlashScript();
    ~CBSlashScript();
};

