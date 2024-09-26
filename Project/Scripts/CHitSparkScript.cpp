#include "pch.h"
#include "CHitSparkScript.h"

CHitSparkScript::CHitSparkScript()
	: CScript(SCRIPT_TYPE::HITSPARKSCRIPT)
{
}

CHitSparkScript::~CHitSparkScript()
{
}

void CHitSparkScript::Begin()
{
	Ptr<CFlipBook> pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\HitSpark.flip");
	FlipBookComponent()->AddFlipBook(0, pFlipBook);
	FlipBookComponent()->Play(0, 10, false);
}

void CHitSparkScript::Tick()
{
	if (FlipBookComponent()->IsFinish())
	{
		DeleteObject(GetOwner());
	}
}

void CHitSparkScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider)
{
}

void CHitSparkScript::SaveToFile(FILE* _File)
{
}

void CHitSparkScript::LoadFromFile(FILE* _File)
{
}



