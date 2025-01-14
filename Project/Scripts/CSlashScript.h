#pragma once
#include <Engine/CScript.h>

class CSlashScript :
    public CScript
{
private:
    Ptr<CPrefab>    m_SparkPref;

    float           m_Speed;

    int             m_AnimIdx;
    int static      m_SlashIdx;

public:
    void SetAnimIdx(int _Idx) { m_AnimIdx = _Idx; }

public:
    virtual void Begin() override;
    virtual void Tick() override;

    virtual void BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider) override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;

public:
    CLONE(CSlashScript);
    CSlashScript();
    ~CSlashScript();
};

