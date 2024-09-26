#pragma once
#include "CComponent.h"

class CCollider2D :
    public CComponent
{
private:
    Vec3    m_Offset;
    Vec3    m_Scale;        // 배율 or 절대크기
    Matrix  m_matColWorld;  // 충돌체의 최종 월드 상태
    int     m_OverlapCount;

    bool    m_IndependentScale; // 오브젝트의 크기에 영향을 받을지 여부
    bool    m_Active;

    Vec3    m_CollisionPoint;

public:
    void SetOffset(Vec3 _Offset) { m_Offset = _Offset; }
    void SetScale(Vec3 _Scale) { m_Scale = _Scale; }
    void SetIndependentScale(bool _Set) { m_IndependentScale = _Set; }
    void SetActive(bool _Set) { m_Active = _Set; }
    void SetCollisionPoint(Vec3 _Point) { m_CollisionPoint = _Point; }

    bool IsIndependentScale() { return m_IndependentScale; }
    Vec3 GetOffset() { return m_Offset; }
    Vec3 GetScale() { return m_Scale; }
    Vec3 GetWorldPos() { return m_matColWorld.Translation(); }
    const Matrix& GetWorldMat() { return m_matColWorld; }
    Vec3 GetCollisionPoint() { return m_CollisionPoint; }

    int  GetOverlapCount() { return m_OverlapCount; }
    bool IsActive() { return m_Active; }

public:
    virtual void BeginOverlap(CCollider2D* _Other);
    virtual void Overlap(CCollider2D* _Other);
    virtual void EndOverlap(CCollider2D* _Other);

public:
    virtual void FinalTick() override;
    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;


public:
    CLONE(CCollider2D);
    CCollider2D();
    CCollider2D(const CCollider2D& _Origin);
    ~CCollider2D();
};

