#pragma once
#include <Engine/CScript.h>

class CFireDragonScript :
    public CScript
{
private:
    Vec3    m_Pos;

    float   amplitude;  // sin ����
    float   frequency;  // sin �ֱ�
    float   speed;



public:
    virtual void Begin() override;
    virtual void Tick() override;

    virtual void BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider) override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;

public:
    CLONE(CFireDragonScript);
    CFireDragonScript();
    ~CFireDragonScript();
};

