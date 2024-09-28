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
        HIT,
        FIREDRAGON,
        FIREBALL,
    };

    enum class AtkState
    {
        NONE,
        ATTACK1,
        ATTACK2,
    };

    enum class CollisionDir
    {
        NONE,
        RIGHT,
        LEFT,
        UP,
        DOWN,
    };

private:
    float                   m_HP;
    float                   m_MP;
    int                     m_SlashDmg;
    bool                    m_IsDead;
    Ptr<CPrefab>            m_TeleportPref;

    Ptr<CTexture>           m_Texture;
    Ptr<CPrefab>            m_SlashPref;

    eState                  m_State;
    AtkState                m_AtkState;

    eDIR                    m_PrevDirection;
    eDIR                    m_Direction;
    eDIR                    m_AttackDir;
    Vec2                    m_MouseDir;
    Vec2                    m_MovedPos;

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
    Vec3                    m_SlashRot;

    float	                m_HitTime;
    float	                m_KnockBackSpeed;
    float	                m_KnockBackTime;
    float	                m_KnockBackAge;
    Vec3                    m_HitDir;


    int                     m_KeyTapCount;
    int                     m_AttackCount;
    float                   m_AttackCooldown;

    int                     m_Attribute;

    CollisionDir            m_CollisionDir;
    int                     m_CollisionCount;

private:
    void KeyInput();
    void Idle();
    void Move();
    void Attack();
    void Dash();
    void KnockBack();

    void ExitState();

    void MousePosCheck();
    void LoadFlipBook();

public:
    float GetSpeed() { return m_Speed; }
    int GetSlashDamage() { return m_SlashDmg; }

    void SetSpeed(float _Speed) { m_Speed = _Speed; }


public:
    virtual void Begin() override;
    virtual void Tick() override;

    virtual void BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider) override;
    virtual void Overlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider) override;
    virtual void EndOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider) override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;

public:
    CLONE(CPlayerScript);
    CPlayerScript();
    ~CPlayerScript();
};