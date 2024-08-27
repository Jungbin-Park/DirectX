#include "pch.h"
#include "Content.h"

#include "TreeUI.h"

Content::Content()
{
	m_Tree = new TreeUI;
	m_Tree->SetName("ContentTree");
	AddChild(m_Tree);

	m_Tree->AddNode("Parent");
}

Content::~Content()
{
}

void Content::Update()
{
	// AssetMgr 에서 받은 Asset 정보를 띄워준다.
}
