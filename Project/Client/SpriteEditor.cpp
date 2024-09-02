#include "pch.h"
#include "SpriteEditor.h"


#include "CEditorMgr.h"
#include "SE_AtlasView.h"
#include "SE_Detail.h"

SpriteEditor::SpriteEditor()
{
}

SpriteEditor::~SpriteEditor()
{
}

void SpriteEditor::Init()
{
	m_AtlasView = (SE_AtlasView*)CEditorMgr::GetInst()->FindEditorUI("SE_AtlasView");
	m_Detail = (SE_Detail*)CEditorMgr::GetInst()->FindEditorUI("SE_Detail");
}

void SpriteEditor::Update()
{
}
