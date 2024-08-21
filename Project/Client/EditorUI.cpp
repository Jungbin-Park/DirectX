#include "pch.h"
#include "EditorUI.h"


UINT EditorUI::m_GlobalID = 0;

EditorUI::EditorUI()
	: m_Active(true)
	, m_Parent(nullptr)
	, m_ID(m_GlobalID++)
{

}

EditorUI::~EditorUI()
{
	Delete_Vec(m_vecChildUI);
}

void EditorUI::Tick()
{
	if (!m_Active)
		return;


	// 최상위 부모 UI 인 경우
	if (nullptr == m_Parent)
	{
		ImGui::Begin(m_FullName.c_str(), &m_Active);

		Update();

		for (size_t i = 0; i < m_vecChildUI.size(); ++i)
		{
			m_vecChildUI[i]->Tick();
		}

		ImGui::End();
	}

	// 자식 타입 UI 인 경우
	else
	{
		ImGui::BeginChild(m_FullName.c_str());

		Update();

		for (size_t i = 0; i < m_vecChildUI.size(); ++i)
		{
			m_vecChildUI[i]->Tick();
		}

		ImGui::EndChild();
	}
}

void EditorUI::AddChild(EditorUI* _UI)
{
	_UI->m_Parent = this;
	m_vecChildUI.push_back(_UI);
}

void EditorUI::SetName(const string& _Name)
{
	m_Name = _Name;

	// ID 문자열 생성
	m_FullName = m_Name;
	char szNum[50] = {};
	_itoa_s(m_ID, szNum, 10);
	m_FullName = m_FullName + "##" + szNum;
}
