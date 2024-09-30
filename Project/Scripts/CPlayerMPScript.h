#pragma once
#include <Engine/CScript.h>

class CPlayerMPScript :
    public CScript
{
private:
    float			m_MaxPlayerMP;
    float			m_CurPlayerMP;
    float			m_DamageHP;

public:
    virtual void Begin() override;
    virtual void Tick() override;

    virtual void BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider) override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;

public:
    CLONE(CPlayerMPScript);
    CPlayerMPScript();
    ~CPlayerMPScript();
};

