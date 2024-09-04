#pragma once
#include "SE_Sub.h"

class SE_Detail :
    public SE_Sub
{
private:
    Ptr<CTexture>   m_AtlasTex;
    CSprite*        m_CurSprite;
    ImVec2          m_SpriteLT;
    ImVec2          m_SpriteRB;
    ImVec2          m_SpriteSize;

    Vec2            m_Background;

    bool            m_Active;

private:
    void Atlas();
    void AtlasInfo();
    void SelectedSpriteInfo();
    void CalcBackgroundSize(Vec2 _SpriteSize);
    void SaveSprite();

public:
    void SetAtlasTex(Ptr<CTexture> _Tex);

public:
    virtual void Init() override;
    virtual void Update() override;

private:
    void SelectTexture(DWORD_PTR _ListUI);

public:
    SE_Detail();
    ~SE_Detail();

};
