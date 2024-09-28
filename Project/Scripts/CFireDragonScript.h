#pragma once
#include <Engine/CScript.h>

class CFireDragonScript :
    public CScript
{
private:
    static int      m_GlobalNum;
    int             m_Num;

    CGameObject*    m_Player;
    Vec3            m_Pos;
    Vec3            m_Dir;

    float           amplitude;  // sin ÁøÆø
    float           frequency;  // sin ÁÖ±â
    float           speed;


    Ptr<CPrefab>    m_SparkPref;


public:
    virtual void Begin() override;
    virtual void Tick() override;

    virtual void BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider) override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;

public:
    CLONE(CFireDragonScript);
    CFireDragonScript();
    ~CFireDragonScript();
};

