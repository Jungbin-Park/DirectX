#include "pch.h"
#include "CameraUI.h"

#include <Engine/CGameObject.h>
#include <Engine/CCamera.h>

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CLayer.h>

CameraUI::CameraUI()
	: ComponentUI(COMPONENT_TYPE::CAMERA)
	, m_ShowLayerCheck(false)
{
}

CameraUI::~CameraUI()
{
}

void CameraUI::Update()
{
	Title();

    CCamera* pCam = GetTargetObject()->Camera();

    // 카메라 우선순위
    // m_Priority;

    // 레이어 설정
    LayerCheck();

    // 투영방식
    //m_ProjType;

    //float                   m_Width;
    //float                   m_Height;
    //float                   m_AspectRatio;  // 종횡 비
    //float                   m_Far;          // 카메라가 볼 수 있는 시야 거리
    //float                   m_FOV; // Field Of View (시야 범위, 시야 각)
}

void CameraUI::LayerCheck()
{
    ImGui::Text("Layer Check");
    ImGui::SameLine(100);
    if (ImGui::Button("Show##LayerCheckBtn", ImVec2(50.f, 18.f)))
    {
        m_ShowLayerCheck ? m_ShowLayerCheck = false : m_ShowLayerCheck = true;
    }

    if (!m_ShowLayerCheck)
        return;


    CCamera* pCam = GetTargetObject()->Camera();

    bool bLayer[32] = {};
    for (int i = 0; i < 32; ++i)
    {
        bLayer[i] = pCam->GetLayerCheck(i);
    }

    int ChangedIdx = -1;
    if (ImGui::BeginTable("##LayerCheckTable", 2, ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings | ImGuiTableFlags_Borders))
    {
        for (int i = 0; i < 32; i++)
        {
            char label[32];
            sprintf_s(label, "Layer %d", i);
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            if (ImGui::Selectable(label, &bLayer[i], ImGuiSelectableFlags_SpanAllColumns))
            {
                ChangedIdx = i;
            }

            wstring wlayerName = CLevelMgr::GetInst()->GetCurrentLevel()->GetLayer(i)->GetName();
            string layerName(wlayerName.begin(), wlayerName.end());
            ImGui::TableNextColumn();
            ImGui::Text(layerName.c_str());
        }
        ImGui::EndTable();
    }

    if (ChangedIdx != -1)
    {
        pCam->SetLayer(ChangedIdx, bLayer[ChangedIdx]);
    }
}



//const char* items[] = { "AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIII", "JJJJ", "KKKK", "LLLLLLL", "MMMM", "OOOOOOO" };
//static int item_current_idx = 0; // Here we store our selection data as an index.
//
//const char* combo_preview_value = items[item_current_idx];
//
//static bool bOpen = false;
//
//if (ImGui::BeginCombo("combo 1", combo_preview_value))
//{
//    for (int n = 0; n < IM_ARRAYSIZE(items); n++)
//    {
//        const bool is_selected = (item_current_idx == n);
//        if (ImGui::Selectable(items[n], is_selected))
//            item_current_idx = n;
//
//        // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
//        if (is_selected)
//            ImGui::SetItemDefaultFocus();
//    }
//    ImGui::EndCombo();
//}