#include "pch.h"
#include "CursorScript.h"

#include <Engine/CDevice.h>

CursorScript::CursorScript()
	:CScript(SCRIPT_TYPE::CURSORSCRIPT)
{
}

CursorScript::~CursorScript()
{
}

void CursorScript::Begin()
{
}

void CursorScript::Tick()
{
	CKeyMgr::GetInst()->MouseCapture(true);

	Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();
	Vec2 vResoltuion = CDevice::GetInst()->GetResolution();

	vMousePos -= Vec2(vResoltuion.x / 2.f, vResoltuion.y / 2.f);
	vMousePos = Vec2(vMousePos.x, -vMousePos.y);

	Transform()->SetRelativePos(Vec3(vMousePos.x, vMousePos.y, 0.f));
}

void CursorScript::SaveToFile(FILE* _File)
{
}

void CursorScript::LoadFromFile(FILE* _File)
{
}


