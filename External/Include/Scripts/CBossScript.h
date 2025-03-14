#pragma once
#include <Engine/CScript.h>

class CBossScript :
    public CScript
{
private:
    CGameObject*            m_Target;
    float                   m_HP;
    bool                    m_Dead;

    Ptr<CPrefab>	        m_CrystalPref;

    // Lance
    vector<Ptr<CPrefab>>    m_vecLance;
    float                   m_Angle;

    // Slash

private:
    void LoadAnimation();

public:
    float GetHP() { return m_HP; }

public:
    virtual void Begin() override;
    virtual void Tick() override;

    virtual void BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider) override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;

public:
    CLONE(CBossScript);
    CBossScript();
    ~CBossScript();
};

