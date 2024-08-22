#pragma once
#include "ComponentUI.h"
class ParticleSystemUI :
    public ComponentUI
{
private:
    virtual void Update() override;

public:
    ParticleSystemUI();
    ~ParticleSystemUI();
};

