#pragma once
#include "EditorUI.h"

class TreeNode
{
private:
    string              m_Name;
    TreeNode*           m_ParentNode;
    vector<TreeNode*>   m_vecChildNode;

public:
    void SetName(const string& _Name) { m_Name = _Name; }
    const string& GetName() { return m_Name; }

    void AddChildNode(TreeNode* _Node) { m_vecChildNode.push_back(_Node); }

public:
    void Update();

public:
    TreeNode();
    ~TreeNode();
};


class TreeUI :
    public EditorUI
{
private:
    TreeNode* m_Root;


public:
    void AddNode(const string& _Name);

public:
    virtual void Update() override;

public:
    TreeUI();
    ~TreeUI();
};

