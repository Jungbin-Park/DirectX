#pragma once
#include "CAsset.h"

class CSprite :
    public CAsset
{
private:
    Ptr<CTexture>   m_Atlas;
    Vec2            m_LeftTop;  // UV ÁÂÇ¥°è
    Vec2            m_Slice;    // UV ÁÂÇ¥°è

public:
    Ptr<CTexture> GetAtlasTexture() { return m_Atlas; }
    Vec2 GetLeftTopUV() { return m_LeftTop; }
    Vec2 GetSliceUV() { return m_Slice; }

public:
    void Create(Ptr<CTexture> _Atlas, Vec2 _LeftTopPixel, Vec2 _SlicePixel);

    virtual int Load(const wstring& _FilePath) { return S_OK; };
    virtual int Save(const wstring& _FilePath) { return S_OK; };

public:
    CSprite();
    ~CSprite();
};

