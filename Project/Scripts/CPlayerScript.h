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
        DEAD,
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
    

    eState                  m_State;
    AtkState                m_AtkState;

    eDIR                    m_PrevDirection;
    eDIR                    m_Direction;
    eDIR                    m_AttackDir;
    Vec2                    m_MouseDir;
    Vec2                    m_MovedPos;

    // Move
    float                   m_Speed;
    float                   m_DashSpeed;
    float                   m_DashTime;
    float                   m_DashDuration;
    bool                    m_DashFinish;

    // Slash
    Ptr<CPrefab>            m_SlashPref;
    float                   m_AtkDashSpeed;
    float                   m_AtkDashTime;
    float                   m_AtkDashDuration;
    bool                    m_AttackFinish;
    Vec3                    m_SlashPos;
    Vec3                    m_SlashRot;
    int                     m_AttackCount;
    float                   m_AttackCooldown;

    // ShootFireDragon
    Ptr<CPrefab>            m_FireDragonPref;
    Vec3                    m_FireDragonPos;
    Vec3                    m_FireDragonRot;
    int                     m_FireDragonCount;
    int                     m_SkillAnimCount;
    float                   m_FireDragonCooldown;

    // Hit
    float	                m_HitTime;
    float	                m_KnockBackSpeed;
    float	                m_KnockBackTime;
    float	                m_KnockBackAge;
    Vec3                    m_HitDir;

    // Sound
    Ptr<CSound>             m_WalkSound;
    Ptr<CSound>             m_SlashSound;
    Ptr<CSound>             m_FireDragonSound;
    Ptr<CSound>             m_DashSound;
    Ptr<CSound>             m_HitSound;
    Ptr<CSound>             m_DeadSound;


    int                     m_KeyTapCount;
    int                     m_Attribute;

    CollisionDir            m_CollisionDir;
    int                     m_CollisionCount;

private:
    void KeyInput();
    void Idle();
    void Move();
    void Attack();
    void Dash();
    void FireDragon();
    void KnockBack();
    void ShootFireDragon();

    void ExitState();

    void MousePosCheck();
    void LoadFlipBook();

public:
    float GetSpeed() { return m_Speed; }
    int GetSlashDamage() { return m_SlashDmg; }
    float GetHP() { return m_HP; }
    bool IsDead() { return m_IsDead; }

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