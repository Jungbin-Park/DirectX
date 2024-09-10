#pragma once
#include <Engine/CScript.h>

class CursorScript :
    public CScript
{
private:

public:
    virtual void Begin() override;
    virtual void Tick() override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
public:
    CLONE(CursorScript);
    CursorScript();
    ~CursorScript();
};

