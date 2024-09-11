#pragma once
#include <Engine/CScript.h>

class CSlashScript :
    public CScript
{
private:
    float   m_Speed;

    float   m_Age;
    float   m_Life;

    float   m_CursorAngle;
    Vec3    m_SlashPos;

public:
    void SetCursorAngle(float _Angle) { m_CursorAngle = _Angle; }
    void SetSlashPos(Vec2 _Pos) { m_SlashPos = Vec3(_Pos.x, _Pos.y, 1.f); }

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

