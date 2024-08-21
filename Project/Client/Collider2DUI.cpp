#include "pch.h"
#include "Collider2DUI.h"

#include <Engine/CCollider2D.h>	


Collider2DUI::Collider2DUI()
	: ComponentUI(COMPONENT_TYPE::COLLIDER2D)
{
}

Collider2DUI::~Collider2DUI()
{
}

void Collider2DUI::Update()
{
	Title();

	CCollider2D* pCol = GetTargetObject()->Collider2D();
	Vec3 vScale = pCol->GetScale();
	Vec3 vOffset = pCol->GetOffset();

	// Offset Scale
	ImGui::Text("Scale");
	ImGui::SameLine(100);
	ImGui::DragFloat3("##Scale", vScale);

	// Offset Pos
	ImGui::Text("Offset");
	ImGui::SameLine(100);
	ImGui::DragFloat3("##Offset", vOffset);

	pCol->SetScale(vScale);
	pCol->SetOffset(vOffset);

	// Independent Scale CheckBox
	bool IS = pCol->IsIndependentScale();

	ImGui::Text("Ignore Parent");
	ImGui::SameLine(100);
	if (ImGui::Checkbox("##ColliderIS", &IS))
	{
		pCol->SetIndependentScale(IS);
	}

}