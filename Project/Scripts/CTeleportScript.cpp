#include "pch.h"
#include "CTeleportScript.h"

CTeleportScript::CTeleportScript()
	: CScript(SCRIPT_TYPE::TELEPORTSCRIPT)
{
}

CTeleportScript::~CTeleportScript()
{
}

void CTeleportScript::Begin()
{
	Ptr<CFlipBook> pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\TP.flip");
	FlipBookComponent()->AddFlipBook(0, pFlipBook);
	FlipBookComponent()->Play(0, 10, false);
	
}

void CTeleportScript::Tick()
{
}

void CTeleportScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider)
{
}

void CTeleportScript::SaveToFile(FILE* _File)
{
}

void CTeleportScript::LoadFromFile(FILE* _File)
{
}


