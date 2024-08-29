#pragma once
#include "CEntity.h"

class CAsset :
    public CEntity
{
private:
    wstring             m_Key;
    wstring             m_RelativePath;
    const ASSET_TYPE    m_Type;

    int                 m_RefCount;

public:
    const wstring& GetKey() { return m_Key; }
    const wstring& GetRelativePath() { return m_RelativePath; }
    ASSET_TYPE GetAssetType() { return m_Type; }

protected:
    void SetKey(const wstring& _Key) { m_Key = _Key; }
    void SetRelativePath(const wstring& _Path) { m_RelativePath = _Path; }
    
private:
    void AddRef() { ++m_RefCount; }
    void Release() 
    { 
        --m_RefCount;
        if (m_RefCount <= 0)
            delete this;
    }

    // AssetMgr를 통해 저장/로드가 가능하도록 private
    virtual int Save(const wstring& _RelativePath) = 0;
    virtual int Load(const wstring& _FilePath) = 0;
    
public:
    virtual CAsset* Clone() { return nullptr; }

public:
    CAsset(ASSET_TYPE _Type);
    CAsset(const CAsset& _Other);
    ~CAsset();


    template<typename T>
    friend class Ptr;

    friend class CAssetMgr;
};

