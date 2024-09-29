#pragma once
#include <Engine/CScript.h>

class CManagerScript :
    public CScript
{
private:
    int             m_Score;

    bool            m_bGate;

    Ptr<CPrefab>    m_GateHPref;
    Ptr<CPrefab>    m_GateVPref;

    CGameObject*    m_Player;
    CGameObject*    m_Boss;

    CLevel*         m_CurLevel;
    bool            m_bBGM;
    wchar_t         m_Logo[255];

    Ptr<CSound>     m_BGM;

public:
    void GateClose();
    void GateOpen();

public:
    int GetScore() { return m_Score; }

    void AddScore(int _Score) { m_Score += _Score; }

public:
public:
    CLevel* LoadLevel(const wstring& _FilePath);
    CGameObject* LoadGameObject(FILE* _File);
    CComponent* GetComponent(COMPONENT_TYPE _Type);

public:
    virtual void Begin() override;
    virtual void Tick() override;

    virtual void BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider) override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;

public:
    CLONE(CManagerScript);
    CManagerScript();
    ~CManagerScript();
};

