#include "pch.h"
#include "CLanceScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CTransform.h>

CLanceScript::CLanceScript()
	: CScript(SCRIPT_TYPE::LANCESCRIPT)
	, m_Angle(0.f)
	, m_Dist(0.f)
	, m_bRotate(true)
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
	
	FlipBookComponent()->Play(0, 10, false);

	CGameObject* pBoss = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Boss");
	if (pBoss != nullptr)
		m_Boss = pBoss;

	Vec3 vBPos = m_Boss->Transform()->GetRelativePos();
	Vec3 vPos = Transform()->GetRelativePos();
	Vec3 vRelativePos = vPos - vBPos;

	m_Angle = atan2(vRelativePos.y, vRelativePos.x);
	m_Dist = sqrt(vRelativePos.x * vRelativePos.x + vRelativePos.y * vRelativePos.y);
}

void CLanceScript::Tick()
{
	Vec3 vPlayerPos = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Player")->Transform()->GetRelativePos();
	Vec3 vBPos = m_Boss->Transform()->GetRelativePos();
	Vec3 vBRot = m_Boss->Transform()->GetRelativeRotation();
	Vec3 vPos = Transform()->GetRelativePos();
	Vec3 vPDir = vPlayerPos - vPos;
	Vec3 vBPDir = vPlayerPos - vBPos;

	vPDir.Normalize();
	vBPDir.Normalize();
	
	// 전체 회전
	//m_Angle = atan2(vBPDir.y, vBPDir.x);
	m_Angle;

	float newX = vBPos.x + m_Dist * cosf(m_Angle);
	float newY = vBPos.y + m_Dist * sinf(m_Angle);

	GetOwner()->Transform()->SetRelativePos(Vec3(newX, newY, 0.f));

	// 본인 기준 회전
	float angle;
	angle = atan2(vPDir.y, vPDir.x);

	Vec3 vRot = Transform()->GetRelativeRotation();
	vRot.z = angle - XM_PI / 2.f;

	Transform()->SetRelativeRotation(vRot);


	
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


