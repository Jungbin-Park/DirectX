#include "pch.h"
#include "CChargeEffectScript.h"

CChargeEffectScript::CChargeEffectScript()
	: CScript(SCRIPT_TYPE::CHARGEEFFECTSCRIPT)
{
}

CChargeEffectScript::~CChargeEffectScript()
{
}

void CChargeEffectScript::Begin()
{
	Ptr<CFlipBook> pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\FireBallCharge.flip");
	FlipBookComponent()->AddFlipBook(0, pFlipBook);
	FlipBookComponent()->Play(0, 20, false);
}

void CChargeEffectScript::Tick()
{
	if (FlipBookComponent()->IsFinish())
		DeleteObject(GetOwner());
}

void CChargeEffectScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider)
{
}

void CChargeEffectScript::Overlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider)
{
}

void CChargeEffectScript::EndOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider)
{
}

void CChargeEffectScript::SaveToFile(FILE* _File)
{
}

void CChargeEffectScript::LoadFromFile(FILE* _File)
{
}



