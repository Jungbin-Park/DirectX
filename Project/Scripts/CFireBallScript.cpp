#include "pch.h"
#include "CFireBallScript.h"

#include <Engine/CLevel.h>
#include <Engine/CLevelMgr.h>

CFireBallScript::CFireBallScript()
	: CScript(SCRIPT_TYPE::FIREBALLSCRIPT)
	, m_Sound(nullptr)
	, m_HitSound(nullptr)
	, m_Speed(700.f)
	, m_bHit(false)
{
}

CFireBallScript::~CFireBallScript()
{
	if (m_Sound != nullptr)
		m_Sound->Stop();
	if (m_HitSound != nullptr)
		m_HitSound->Stop();
}

void CFireBallScript::Begin()
{
	m_Player = CLevelMgr::GetInst()->FindObjectByName(L"Player");

	Vec3 vPlayerPos = m_Player->Transform()->GetRelativePos();
	Vec3 vPos = Transform()->GetRelativePos();
	m_Dir = vPos - vPlayerPos;
	m_Dir.Normalize();

	Ptr<CFlipBook> pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\NFireBall.flip");
	FlipBookComponent()->AddFlipBook(0, pFlipBook);
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\NFireBallHit.flip");
	FlipBookComponent()->AddFlipBook(1, pFlipBook);
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\SFireBall.flip");
	FlipBookComponent()->AddFlipBook(2, pFlipBook);
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\SFireBallHit.flip");
	FlipBookComponent()->AddFlipBook(3, pFlipBook);

	FlipBookComponent()->Play(2, 10, true);

	m_Sound = CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\FireBall.wav");
	m_HitSound = CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\FireBallHit.wav");
	m_bHit = false;

	m_Sound->Play(1, 0.3f, true);

	Collider2D()->SetActive(true);
}

void CFireBallScript::Tick()
{
	if (m_bHit)
	{
		if (FlipBookComponent()->IsFinish())
		{
			DeleteObject(GetOwner());
		}
	}
	else
	{
		Vec3 vPos = Transform()->GetRelativePos();

		vPos += m_Dir * DT * m_Speed;

		Transform()->SetRelativePos(vPos);
	}
}

void CFireBallScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider)
{
	Vec3 vPos = _OwnCollider->GetCollisionPoint();
	m_HitSound->Play(1, 0.1f, true);

	m_bHit = true;
	Transform()->SetRelativeScale(Vec3(200.f, 200.f, 0.f));
	Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));
	FlipBookComponent()->Play(3, 10, false);
}

void CFireBallScript::SaveToFile(FILE* _File)
{
}

void CFireBallScript::LoadFromFile(FILE* _File)
{
}



