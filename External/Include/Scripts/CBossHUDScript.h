#pragma once
#include <Engine/CScript.h>

class CBossHUDScript :
    public CScript
{
private:
    float			m_MaxPlayerHP;
    float			m_CurPlayerHP;
    float			m_DamageHP;

public:
    virtual void Begin() override;
    virtual void Tick() override;

    virtual void BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider) override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;

public:
    CLONE(CBossHUDScript);
    CBossHUDScript();
    ~CBossHUDScript();
};

