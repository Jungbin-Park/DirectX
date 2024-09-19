#pragma once
#include <Engine/CScript.h>

class CGhoulScript :
    public CScript
{
private:
    float                   m_Speed;
    float                   m_HP;
    float                   m_Cooldown;

    float                   m_DetectRange;
    float                   m_AttackRange;


public:
    float GetSpeed() { return m_Speed; }

public:
    virtual void Begin() override;
    virtual void Tick() override;

    virtual void BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider) override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;

public:
    CLONE(CGhoulScript);
    CGhoulScript();
    ~CGhoulScript();
};

