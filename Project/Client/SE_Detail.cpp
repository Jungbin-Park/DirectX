#include "pch.h"
#include "SE_Detail.h"

#include "CEditorMgr.h"
#include "ListUI.h"
#include "TreeUI.h"

#include "SE_AtlasView.h"

#include <Engine/CAsset.h>
#include <Engine/CSprite.h>

#include <Engine/CAssetMgr.h>
#include <Engine/CPathMgr.h>

SE_Detail::SE_Detail()
	: m_CurSprite(nullptr)
	, m_Active(false)
	, m_FlipHorizontal(false)
{
}

SE_Detail::~SE_Detail()
{
}

void SE_Detail::Init()
{
}

void SE_Detail::Update()
{
	Atlas();

	AtlasInfo();

	if (m_Active)
		SaveSprite();
}

void SE_Detail::Atlas()
{
	string TexName;

	if (nullptr != m_AtlasTex)
		TexName = string(m_AtlasTex->GetKey().begin(), m_AtlasTex->GetKey().end());

	ImGui::Text("Atlas Texture");
	ImGui::SameLine(120);
	ImGui::SetNextItemWidth(150.f);
	ImGui::InputText("##AtlasTex", (char*)TexName.c_str(), ImGuiInputTextFlags_::ImGuiInputTextFlags_ReadOnly);

	if (ImGui::BeginDragDropTarget())
	{
		const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ContentTree");
		if (payload)
		{
			TreeNode** ppNode = (TreeNode**)payload->Data;
			TreeNode* pNode = *ppNode;

			Ptr<CAsset> pAsset = (CAsset*)pNode->GetData();
			if (ASSET_TYPE::TEXTURE == pAsset->GetAssetType())
			{
				SetAtlasTex((CTexture*)pAsset.Get());
			}
		}

		ImGui::EndDragDropTarget();
	}

	ImGui::SameLine();
	if (ImGui::Button("##AtlasTexBtn", ImVec2(18.f, 18.f)))
	{
		ListUI* pListUI = (ListUI*)CEditorMgr::GetInst()->FindEditorUI("List");
		pListUI->SetName("Texture");
		vector<string> vecTexNames;
		CAssetMgr::GetInst()->GetAssetNames(ASSET_TYPE::TEXTURE, vecTexNames);
		pListUI->AddList(vecTexNames);
		pListUI->AddDelegate(this, (DELEGATE_1)&SE_Detail::SelectTexture);
		pListUI->SetActive(true);
	}
}

void SE_Detail::AtlasInfo()
{
	// 해상도
	UINT width = 0;
	UINT height = 0;

	if (nullptr != m_AtlasTex)
	{
		width = m_AtlasTex->Width();
		height = m_AtlasTex->Height();
	}

	char buff[50] = {};
	sprintf_s(buff, "%d", width);

	ImGui::Text("Width");
	ImGui::SameLine(100);
	ImGui::InputText("##TextureWidth", buff, 50, ImGuiInputTextFlags_ReadOnly);

	sprintf_s(buff, "%d", height);
	ImGui::Text("Height");
	ImGui::SameLine(100);
	ImGui::InputText("##TextureHeight", buff, 50, ImGuiInputTextFlags_ReadOnly);

	ImGui::SeparatorText("Select Sprite");

	SelectedSpriteInfo();
}

void SE_Detail::SelectedSpriteInfo()
{
	// 해상도
	UINT width = 0;
	UINT height = 0;

	if (nullptr != m_AtlasTex)
	{
		width = m_AtlasTex->Width();
		height = m_AtlasTex->Height();
	}

	// Sprite Image
	m_SpriteLT = GetAtlasView()->GetSpriteLT();
	m_SpriteRB = GetAtlasView()->GetSpriteRB();
	m_SpriteSize = ImVec2(m_SpriteRB.x - m_SpriteLT.x, m_SpriteRB.y - m_SpriteLT.y);

	ImVec2 uv_min = ImVec2(m_SpriteLT.x / width, m_SpriteLT.y / height);
	ImVec2 uv_max = ImVec2((m_SpriteLT.x + m_SpriteSize.x) / width, (m_SpriteLT.y + m_SpriteSize.y) / height);

	ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	ImVec4 border_col = ImVec4(0.7f, 0.7f, 0.7f, 1.0f);

	if (m_FlipHorizontal)
	{
		ImGui::Image(m_AtlasTex->GetSRV().Get(), ImVec2(100.f, 100.f)
			, ImVec2(uv_max.x, uv_min.y), ImVec2(uv_min.x, uv_max.y), tint_col, border_col);
	}
	else
	{
		ImGui::Image(m_AtlasTex->GetSRV().Get(), ImVec2(100.f, 100.f)
			, uv_min, uv_max, tint_col, border_col);
	}

	

	// Sprite Info
	float ArrSpriteLT[] = { m_SpriteLT.x, m_SpriteLT.y };
	ImGui::InputFloat2("LeftTop", ArrSpriteLT);

	float ArrSpriteRB[] = { m_SpriteRB.x, m_SpriteRB.y };
	ImGui::InputFloat2("RightBottom", ArrSpriteRB);

	float ArrSpriteSize[] = { m_SpriteSize.x, m_SpriteSize.y };
	ImGui::InputFloat2("Size", ArrSpriteSize);

	ImGui::Spacing();

	if (ImGui::Button("Flip Horizontal", ImVec2(100.f, 18.f)))
	{
		if (m_FlipHorizontal)
			m_FlipHorizontal = false;
		else
			m_FlipHorizontal = true;
	}

	ImGui::SetCursorPosX((ImGui::GetWindowSize().x * 0.5f) + 50.f);
	ImGui::SetCursorPosY((ImGui::GetWindowSize().y * 0.5f));
	if (ImGui::Button("Save Sprite", ImVec2(100.f, 18.f)))
	{
		m_Active = true;
	}

	ImGui::Separator();
}

void SE_Detail::SetAtlasTex(Ptr<CTexture> _Tex)
{
	m_AtlasTex = _Tex;
	GetAtlasView()->SetAtlasTex(m_AtlasTex);
}


void SE_Detail::SelectTexture(DWORD_PTR _ListUI)
{
	ListUI* pListUI = (ListUI*)_ListUI;
	string strName = pListUI->GetSelectName();

	if (strName == "None")
	{
		m_AtlasTex = nullptr;
		return;
	}

	wstring strAssetName = wstring(strName.begin(), strName.end());

	Ptr<CTexture> pTex = CAssetMgr::GetInst()->FindAsset<CTexture>(strAssetName);

	assert(pTex.Get());

	SetAtlasTex(pTex);
}

void SE_Detail::CalcBackgroundSize(Vec2 _SpriteSize)
{

	if (_SpriteSize.x <= 45.f && _SpriteSize.y <= 45.f)
		m_Background = Vec2(45.f, 45.f);
	else if (45.f < _SpriteSize.x && _SpriteSize.x <= 50.f &&
		45.f < _SpriteSize.y && _SpriteSize.y <= 50.f)
		m_Background = Vec2(50.f, 50.f);
	else if (50.f < _SpriteSize.x && _SpriteSize.x <= 60.f &&
		50.f < _SpriteSize.y && _SpriteSize.y <= 60.f)
		m_Background = Vec2(60.f, 60.f);
	else if (60.f < _SpriteSize.x && _SpriteSize.x <= 70.f &&
		60.f < _SpriteSize.y && _SpriteSize.y <= 70.f)
		m_Background = Vec2(70.f, 70.f);
	else if (70.f < _SpriteSize.x && _SpriteSize.x <= 80.f &&
		70.f < _SpriteSize.y && _SpriteSize.y <= 80.f)
		m_Background = Vec2(80.f, 80.f);
	else if (80.f < _SpriteSize.x && _SpriteSize.x <= 90.f &&
		80.f < _SpriteSize.y && _SpriteSize.y <= 90.f)
		m_Background = Vec2(90.f, 90.f);
	else if (90.f < _SpriteSize.x && _SpriteSize.x <= 100.f &&
		90.f < _SpriteSize.y && _SpriteSize.y <= 100.f)
		m_Background = Vec2(100.f, 100.f);
	else if (100.f < _SpriteSize.x && _SpriteSize.x <= 150.f &&
		100.f < _SpriteSize.y && _SpriteSize.y <= 150.f)
		m_Background = Vec2(150.f, 150.f);
	else
		m_Background = Vec2(200.f, 200.f);
}

void SE_Detail::SaveSprite()
{
	ImGui::OpenPopup("Save Sprite");

	/*ImVec2 center = ImGui::GetMainViewport()->GetCenter();
	ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));*/

	if (ImGui::BeginPopupModal("Save Sprite", NULL, 0))
	{
		ImGui::Text("Enter Sprite Name");
		ImGui::Text("");
		static char cBuff[50] = {};
		ImGui::InputText("##SaveName", cBuff, sizeof(cBuff));
		ImGui::Text("");

		if (ImGui::Button("Save", ImVec2(120, 0)))
		{
			m_Active = false;

			m_CurSprite = new CSprite;
			Vec2 vSpriteLT = { m_SpriteLT.x, m_SpriteLT.y };
			Vec2 vSpriteSize = { m_SpriteSize.x, m_SpriteSize.y };

			if (m_FlipHorizontal)
			{
				m_CurSprite->Create(m_AtlasTex, vSpriteLT, vSpriteSize, true);
			}
			else
			{
				m_CurSprite->Create(m_AtlasTex, vSpriteLT, vSpriteSize);
			}
			CalcBackgroundSize(vSpriteSize);
			m_CurSprite->SetBackground(Vec2(m_Background.x, m_Background.y));

			wstring strContentPath = CPathMgr::GetInst()->GetContentPath();
			std::wstring wsBuff = std::wstring(cBuff, cBuff + strlen(cBuff));
			m_CurSprite->Save(strContentPath + L"sprite\\" + wsBuff + L".sprite");
			ImGui::CloseCurrentPopup();
		}

		ImGui::SetItemDefaultFocus();
		ImGui::SameLine();
		if (ImGui::Button("Cancel", ImVec2(120, 0)))
		{
			m_Active = false;
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
}
