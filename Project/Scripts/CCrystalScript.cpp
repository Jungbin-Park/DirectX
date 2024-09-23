#include "pch.h"
#include "CCrystalScript.h"

CCrystalScript::CCrystalScript()
	: CScript(SCRIPT_TYPE::CRYSTALSCRIPT)
{
}

CCrystalScript::~CCrystalScript()
{
}

void CCrystalScript::Begin()
{
	// Spawn
	Ptr<CFlipBook> pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\Crystal.flip");
	FlipBookComponent()->AddFlipBook(0, pFlipBook);
	FlipBookComponent()->Play(0, 5, false);
}

void CCrystalScript::Tick()
{
	if (FlipBookComponent()->IsFinish())
		DeleteObject(GetOwner());
}

void CCrystalScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider)
{
}

void CCrystalScript::SaveToFile(FILE* _File)
{
}

void CCrystalScript::LoadFromFile(FILE* _File)
{
}



