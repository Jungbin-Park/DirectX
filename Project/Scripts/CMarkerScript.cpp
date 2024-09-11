#include "pch.h"
#include "CMarkerScript.h"

#include <Engine/define.h>
#include <Engine/CDevice.h>
#include "CSlashScript.h"

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
	Vec3 vPlayerRot = GetOwner()->GetParent()->Transform()->GetRelativeRotation();

	Vec2 pPos = Vec2(vPlayerPos.x, vPlayerPos.y);
	vMousePos += pPos;

	Vec2 vMouseDir = vMousePos - pPos;
	vMouseDir.Normalize();

	float angle;

	if (vPlayerRot.y == XM_PI)
		angle = atan2(vMouseDir.y, -vMouseDir.x);
	else
		angle = atan2(vMouseDir.y, vMouseDir.x);

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


