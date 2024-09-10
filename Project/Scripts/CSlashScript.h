#pragma once
#include <Engine/CScript.h>

class CSlashScript :
    public CScript
{
private:
    float   m_Speed;

    float   m_Age;
    float   m_Life;

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

