#pragma once
#include "CAsset.h"

class CPrefab :
    public CAsset
{
private:
    class CGameObject* m_ProtoObject;

public:
    void SetProtoObject(CGameObject* _Object) { m_ProtoObject = _Object; }
    CGameObject* Instantiate();

private:
    virtual int Load(const wstring& _FilePath) override;
    virtual int Save(const wstring& _FilePath) override;

public:
    CPrefab();
    ~CPrefab();
};

