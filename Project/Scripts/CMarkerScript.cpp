#include "pch.h"
#include "CMarkerScript.h"

#include <Engine/define.h>
#include <Engine/CDevice.h>

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
	Vec2 vResoltuion = CDevice::GetInst()->GetResolution();

	vMousePos -= Vec2(vResoltuion.x / 2.f, vResoltuion.y / 2.f);
	vMousePos = Vec2(vMousePos.x, -vMousePos.y);
	Vec3 vPlayerPos = GetOwner()->GetParent()->Transform()->GetRelativePos();

	Vec2 pPos = Vec2(vPlayerPos.x, vPlayerPos.y);
	
	Vec2 vMouseDir = vMousePos - pPos;
	vMouseDir.Normalize();

	float angle = atan2(vMouseDir.y, vMouseDir.x);

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


