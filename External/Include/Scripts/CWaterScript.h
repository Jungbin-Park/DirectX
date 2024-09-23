#pragma once
#include <Engine/CScript.h>

class CWaterScript :
    public CScript
{
private:
    bool        m_bShoot;
    Vec2        m_Dir;

    float       m_XPos;
    float       m_YPos;
    float       m_Angle;

    float       m_rotationSpeed;

public:
    void ShootWater(bool _Set, Vec2 _Dir) 
    { 
        m_bShoot = _Set; 
        m_Dir = _Dir;
    }

public:
    virtual void Begin() override;
    virtual void Tick() override;

    virtual void BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider) override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;

public:
    CLONE(CWaterScript);
    CWaterScript();
    ~CWaterScript();
};

