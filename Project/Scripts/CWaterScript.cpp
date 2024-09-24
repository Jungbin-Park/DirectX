#include "pch.h"
#include "CWaterScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CTransform.h>

CWaterScript::CWaterScript()
	: CScript(SCRIPT_TYPE::WATERSCRIPT)
	, m_bShoot(false)
	, m_Dir(Vec3(0.f, 0.f, 0.f))
	, m_rotationSpeed(3.f)
	, m_Boss(nullptr)
	, m_XPos(0.f)
	, m_YPos(0.f)
	, m_Angle(0.f)
	, m_Dist(0.f)
	, m_bRotate(true)
	, m_Speed(500.f)
	, m_bHit(false)
	, m_ShootInitTime(0.f)
	, m_ShootWaterSpacing(0.5f)
	, m_bCountStart(false)
{ 
	
}

CWaterScript::~CWaterScript()
{
}



void CWaterScript::Begin()
{
	SetName(L"CWaterScript");

	Ptr<CFlipBook> pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\WaterBounce.flip");
	FlipBookComponent()->AddFlipBook(0, pFlipBook);
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\WaterExplosion.flip");
	FlipBookComponent()->AddFlipBook(1, pFlipBook);

	FlipBookComponent()->Play(0, 10, true);

	CGameObject* pBoss = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Boss");
	if (pBoss != nullptr)
		m_Boss = pBoss;

	Vec3 vBPos = m_Boss->Transform()->GetRelativePos();
	Vec3 vPos = Transform()->GetRelativePos();
	Vec3 vRelativePos = vPos - vBPos;

	m_Angle = atan2(vRelativePos.y, vRelativePos.x);
	m_Dist = sqrt(vRelativePos.x * vRelativePos.x + vRelativePos.y * vRelativePos.y);
}

void CWaterScript::Tick()
{
	Vec3 vBPos = m_Boss->Transform()->GetRelativePos();
	Vec3 vPos = Transform()->GetRelativePos();

	Vec3 vStartDir = vPos - vBPos;
	vStartDir.Normalize();

	if (m_bRotate)
	{
		m_Angle += DT * m_rotationSpeed;

		float newX = vBPos.x + m_Dist * cosf(m_Angle);
		float newY = vBPos.y + m_Dist * sinf(m_Angle);

		GetOwner()->Transform()->SetRelativePos(Vec3(newX, newY, 0.f));
	}

	if (m_bCountStart)
	{
		m_ShootInitTime += DT;
		if (m_ShootInitTime >= m_ShootWaterSpacing)
		{
			m_bCountStart = false;
			ShootWater();
		}
	}
	
	if (m_bShoot)
	{
		m_bRotate = false;

		vPos += m_Dir * m_Speed * DT;
		Transform()->SetRelativePos(vPos);
	}

	if (m_bHit)
	{
		if (FlipBookComponent()->IsFinish())
			DeleteObject(GetOwner());
	}
}

void CWaterScript::ShootWater()
{
	CGameObject* pTarget = CLevelMgr::GetInst()->FindObjectByName(L"Player");
	Vec3 vDir = pTarget->Transform()->GetRelativePos() - Transform()->GetRelativePos();
	vDir.Normalize();
	
	m_bShoot = true;
	m_Dir = vDir;
}

void CWaterScript::SetShootTime(float _Time)
{
	m_ShootWaterSpacing = _Time; 
	m_bCountStart = true;
}

void CWaterScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider)
{
	if (_OtherObject->GetName() == L"Platform");
	{
		FlipBookComponent()->Play(1, 10, false);
		m_bShoot = false;
		m_bHit = true;
	}
}

void CWaterScript::SaveToFile(FILE* _File)
{
}

void CWaterScript::LoadFromFile(FILE* _File)
{
}


