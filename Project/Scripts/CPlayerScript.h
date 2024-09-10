#pragma once
#include <Engine/CScript.h>

#include <Engine/CGameObject.h>

class CPlayerScript :
    public CScript
{
public:
    enum class eState
    {
        IDLE,
        MOVE,
        ATTACK,
        DASH,
    };

private:
    float                   m_Speed;
    float                   m_DashSpeed;
    float                   m_DashTime;
    float                   m_DashDuration;
    int                     m_Attribute;

    float                   m_CursorAngle;
    Vec3                    m_SlashPos;

    Ptr<CTexture>           m_Texture;
    Ptr<CPrefab>            m_SlashPref;

    eState                  m_State;
    eDirection              m_Direction;

private:
    void ChangeAttribute(int _data);

    void Move();
    void Skill();
    void CursorDirCheck();
    void LoadFlipBook();

public:
    void SetCursorAngle(float _Angle) {m_CursorAngle = _Angle; }

public:
    virtual void Begin() override;
    virtual void Tick() override;

    virtual void BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider) override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;

public:
    CLONE(CPlayerScript);
    CPlayerScript();
    ~CPlayerScript();
};

