#pragma once
#include "CAsset.h"

#include "CSprite.h"

class CFlipBook :
    public CAsset
{
private:
    vector<Ptr<CSprite>>    m_vecSprite;
    float                   m_FPS;

public:
    void AddSprite(Ptr<CSprite> _Sprite) { m_vecSprite.push_back(_Sprite); }
    Ptr<CSprite> GetSprite(int _Idx) { return m_vecSprite[_Idx]; }
    int GetMaxFrameCount() { return (int)m_vecSprite.size(); }
    vector<Ptr<CSprite>>& GetVecSprite() { return m_vecSprite; }

    void SetFPS(float _FPS) { m_FPS = _FPS; }
    float GetFPS() { return m_FPS; }

public:
    void FinalTick();

    virtual int Save(const wstring& _FilePath) override;
    virtual int Load(const wstring& _FilePath) override;
    
public:
    CFlipBook();
    ~CFlipBook();
};

