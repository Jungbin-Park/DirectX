#pragma once
#include "CComponent.h"

class CFSM :
    public CComponent
{


private:
        

public:
    virtual void Init() override;
    virtual void Begin() override;
    virtual void Tick() override;
    virtual void FinalTick() override;

public:
    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
public:
    CLONE(CFSM);
    CFSM();
    ~CFSM();
};

