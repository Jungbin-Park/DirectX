#include "pch.h"
#include "CMarkerScript.h"

#include <Engine/define.h>

CMarkerScript::CMarkerScript()
	: CScript(SCRIPT_TYPE::MARKERSCRIPT)
{
}

CMarkerScript::~CMarkerScript()
{
}

void CMarkerScript::Begin()
{
	
}

void CMarkerScript::Tick()
{
	CKeyMgr::GetInst()->MouseCapture(true);

	Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();
	vMousePos -= Vec2(640.f, 384.f);

	Vec2 pPos = Vec2(Transform()->GetRelativePos().x, Transform()->GetRelativePos().y);

	Vec2 vMouseDir = vMousePos - pPos;
	vMouseDir.Normalize();

	float angle = atan2(vMouseDir.y, -vMouseDir.x);

	Vec3 vRot = Transform()->GetRelativeRotation();
	vRot.z = angle;
	Transform()->SetRelativeRotation(vRot);
}

void CMarkerScript::SaveToFile(FILE* _File)
{
}

void CMarkerScript::LoadFromFile(FILE* _File)
{
}


