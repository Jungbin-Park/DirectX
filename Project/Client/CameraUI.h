#pragma once
#include "ComponentUI.h"

class CameraUI :
    public ComponentUI
{
private:
    bool    m_ShowLayerCheck;

private:
    virtual void Update() override;

private:
    void LayerCheck();

public:
    CameraUI();
    ~CameraUI();
};

