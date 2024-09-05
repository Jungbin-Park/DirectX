#include "pch.h"
#include "TileMapEditor.h"

#include "CEditorMgr.h"
#include "TE_Viewer.h"
#include "TE_Detail.h"

TileMapEditor::TileMapEditor()
	: m_Viewer(nullptr)
	, m_Detail(nullptr)
{
	UseMenuBar(true);
}

TileMapEditor::~TileMapEditor()
{
}

void TileMapEditor::Init()
{
	m_Viewer = (TE_Viewer*)CEditorMgr::GetInst()->FindEditorUI("TE_Viewer");
	m_Detail = (TE_Detail*)CEditorMgr::GetInst()->FindEditorUI("TE_Detail");

	m_Viewer->SetMove(false);
	m_Detail->SetModal(false);

	m_Viewer->m_Owner = this;
	m_Detail->m_Owner = this;
}

void TileMapEditor::Update()
{
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Window"))
		{
			bool Viewer = m_Viewer->IsActive();
			bool Detail = m_Detail->IsActive();

			if (ImGui::MenuItem("TileMap Viewer", nullptr, &Viewer))
			{
				m_Viewer->SetActive(Viewer);
			}

			if (ImGui::MenuItem("TileMap Detail", nullptr, &Detail))
			{
				m_Detail->SetActive(Detail);
			}

			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}
}

void TileMapEditor::Activate()
{
	m_Viewer->SetActive(true);
	m_Detail->SetActive(true);
}

void TileMapEditor::Deactivate()
{
	m_Viewer->SetActive(false);
	m_Detail->SetActive(false);
}


