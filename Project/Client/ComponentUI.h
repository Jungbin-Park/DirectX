#pragma once
#include "EditorUI.h"

class ComponentUI :
    public EditorUI
{
private:
    class CGameObject* m_TargetObject;

public:
    void SetTargetObject(CGameObject* _Object) { m_TargetObject = _Object; }
    CGameObject* GetTargetObject() { return m_TargetObject; }

public:
    ComponentUI();
    ~ComponentUI();
};

