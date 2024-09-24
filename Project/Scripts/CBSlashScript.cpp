#include "pch.h"
#include "CBSlashScript.h"

CBSlashScript::CBSlashScript()
	: CScript(SCRIPT_TYPE::SLASHSCRIPT)
{
}

CBSlashScript::~CBSlashScript()
{
}

void CBSlashScript::Begin()
{
	Ptr<CFlipBook> pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\IceSwordSpawn.flip");
	FlipBookComponent()->AddFlipBook(0, pFlipBook);
	FlipBookComponent()->Play(0, 5, false);
}

void CBSlashScript::Tick()
{
}

void CBSlashScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider)
{
}

void CBSlashScript::SaveToFile(FILE* _File)
{
}

void CBSlashScript::LoadFromFile(FILE* _File)
{
}



