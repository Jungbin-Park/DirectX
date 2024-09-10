#pragma once
#include "CComponent.h"

#include "CFlipBook.h"

// 애니메이션은 하나만 존재
// 다른 플립북 컴포넌트가 하나의 애니메이션을 참조

class CFlipBookComponent :
    public CComponent
{
private:
    vector<Ptr<CFlipBook>>  m_vecFlipBook;  // FlipBook 컴포넌트가 보유한 모든 FlipBook 목록
    Ptr<CFlipBook>          m_CurFlipBook;  // 현재 재생중인 FlipBook
    Ptr<CSprite>            m_CurFrmSprite; // 현재 재생중인 FlipBook에서 현재 프레임 인덱스에 해당하는 스프라이트
    int                     m_CurFrmIdx;    // 현재 재생중인 FlipBook에서 몇 번째 Sprite가 재생 중인지 인덱스 기록
    float                   m_FPS;          // 현재 재생중인 FlipBook의 초당 프레임 진행 수
    float                   m_AccTime;      // 누적 시간 값 체크
    bool                    m_Repeat;       // 반복 여부
    bool                    m_Finish;       // FlipBook 재생이 끝에 도달했는지 여부

public:
    virtual void FinalTick() override;

public:
    void AddFlipBook(int _Idx, Ptr<CFlipBook> _Flipbook);
    Ptr<CFlipBook> FindFlipBook(const wstring& _Key);
    
    Ptr<CSprite> GetCurSprite() { return m_CurFrmSprite; }
    bool IsFinish() { return m_Finish; }

public:
    void Play(int _FlipBookIdx, float _FPS, bool _Repeat);
    void Reset();
    void Binding();
    static void Clear();

public:
    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;

public:
    CLONE(CFlipBookComponent);
    CFlipBookComponent();
    CFlipBookComponent(CFlipBookComponent& _Origin);
    ~CFlipBookComponent();
};

