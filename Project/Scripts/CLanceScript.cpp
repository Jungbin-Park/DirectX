#include "pch.h"
#include "CLanceScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CTransform.h>

CLanceScript::CLanceScript()
	: CScript(SCRIPT_TYPE::LANCESCRIPT)
{
}

CLanceScript::~CLanceScript()
{
}

void CLanceScript::Begin()
{
	SetName(L"CLanceScript");
	Ptr<CFlipBook> pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\IceLanceSpawn.flip");
	FlipBookComponent()->AddFlipBook(0, pFlipBook);
	
	FlipBookComponent()->Play(0, 5, false);

	CGameObject* pBoss = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Boss");
	if (pBoss != nullptr)
		m_Boss = pBoss;

	
}

void CLanceScript::Tick()
{
	/*Vec3 vPlayerPos = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Player")->Transform()->GetRelativePos();
	Vec3 vBPos = m_Boss->Transform()->GetRelativePos();
	Vec3 vPos = Transform()->GetRelativePos();

	Vec3 vDir = vPlayerPos - vBPos;
	Vec3 vRelativePos = vPos - vBPos;

	Vec2 vPerpendicular = Vec2(vDir.y, -vDir.x);

	Vec3 newPos = vBPos + (vPos.x * vPerpendicular);
	Transform()->SetRelativePos(Vec3(newPos.x, newPos.y, 100.f));*/

	/*m_Angle = atan2(vRelativePos.y, vRelativePos.x);
	m_Dist = sqrt(vRelativePos.x * vRelativePos.x + vRelativePos.y * vRelativePos.y);*/
}

void CLanceScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider)
{
}

void CLanceScript::SaveToFile(FILE* _File)
{
}

void CLanceScript::LoadFromFile(FILE* _File)
{
}


