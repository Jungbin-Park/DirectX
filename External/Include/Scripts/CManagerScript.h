#pragma once
#include <Engine/CScript.h>

class CManagerScript :
    public CScript
{
private:
    int     m_Score;

public:
    int GetScore() { return m_Score; }

    void AddScore(int _Score) { m_Score += _Score; }

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

