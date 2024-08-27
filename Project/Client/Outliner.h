#pragma once
#include "EditorUI.h"

class Outliner :
    public EditorUI
{
private:
    class TreeUI* m_Tree;

public:
    virtual void Update() override;

private:
    void RenewLevel();
    void GameObjectClicked(DWORD_PTR _Param);
    void AddGameObject(class TreeNode* pNode, class CGameObject* _Object);

public:
    Outliner();
    ~Outliner();
};

