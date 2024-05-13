#pragma once
#include "CEntity.h"

class CAsset :
    public CEntity
{
private:
    wstring             m_Key;
    wstring             m_RelativePath;
    const ASSET_TYPE    m_Type;

public:
    const wstring& GetKey() { return m_Key; }
    const wstring& GetRelativePath() { return m_RelativePath; }

private:
    void SetKey(const wstring& _Key) { m_Key = _Key; }
    void SetRelativePath(const wstring& _Path) { m_RelativePath = _Path; }
    ASSET_TYPE GetAssetType() { return m_Type; }

public:
    virtual void Binding() = 0;
    virtual CAsset* Clone() { return nullptr; }

public:
    CAsset(ASSET_TYPE _Type);
    ~CAsset();

    friend class CAssetMgr;
};

