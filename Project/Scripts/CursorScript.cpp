#include "pch.h"
#include "CursorScript.h"

#include <Engine/CDevice.h>
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

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

	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	Vec3 vPlayerPos = pCurLevel->FindObjectByName(L"Player")->Transform()->GetRelativePos();

	Vec2 pPos = Vec2(vPlayerPos.x, vPlayerPos.y);
	vMousePos += pPos;

	Transform()->SetRelativePos(Vec3(vMousePos.x, vMousePos.y, 0.f));
}

void CursorScript::SaveToFile(FILE* _File)
{
}

void CursorScript::LoadFromFile(FILE* _File)
{
}


