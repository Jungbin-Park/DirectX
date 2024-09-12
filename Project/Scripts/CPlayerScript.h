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

    enum class AtkState
    {
        NONE,
        ATTACK1,
        ATTACK2,
    };

private:
    Ptr<CTexture>           m_Texture;
    Ptr<CPrefab>            m_SlashPref;

    eState                  m_State;
    AtkState                m_AtkState;

    eDirection              m_PrevDirection;
    eDirection              m_Direction;
    eDirection              m_AttackDir;
    Vec2                    m_MousePos;

    float                   m_Speed;
    float                   m_DashSpeed;
    float                   m_DashTime;
    float                   m_DashDuration;
    bool                    m_DashFinish;

    float                   m_AtkDashSpeed;
    float                   m_AtkDashTime;
    float                   m_AtkDashDuration;
    bool                    m_AttackFinish;
    Vec3                    m_SlashPos;

    
    int                     m_KeyTapCount;
    int                     m_AttackCount;

    int                     m_Attribute;

private:
    void ChangeAttribute(int _data);

    void KeyInput();
    void Idle();
    void Move();
    void Attack();
    void Dash();

    void MousePosCheck();
    void LoadFlipBook();

public:
    

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

