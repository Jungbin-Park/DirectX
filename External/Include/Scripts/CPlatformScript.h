#pragma once
#include <Engine/CScript.h>

#include <Engine/CGameObject.h>

class CPlatformScript :
    public CScript
{
private:
    Vec3    m_WallPos;

public:
    Vec3 GetWallPos() { return m_WallPos; }

public:
    virtual void Begin() override;
    virtual void Tick() override;

    virtual void BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider) override;
    virtual void Overlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider) override;
    virtual void EndOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider) override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;

public:
    CLONE(CPlatformScript);
    CPlatformScript();
    ~CPlatformScript();
};

