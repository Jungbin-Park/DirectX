#pragma once
#include "C:\DirectX\DirectX\External\Include\Engine\CScript.h"

class CMarkerScript :
    public CScript
{
private:

public:
    virtual void Begin() override;
    virtual void Tick() override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
public:
    CLONE(CMarkerScript);
    CMarkerScript();
    ~CMarkerScript();
};

