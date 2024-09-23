#include "pch.h"
#include "CWaterScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CTransform.h>

CWaterScript::CWaterScript()
	: CScript(SCRIPT_TYPE::WATERSCRIPT)
	, m_bShoot(false)
	, m_Dir(Vec2(0.f, 0.f))
	, m_rotationSpeed(10.f)
{
}

CWaterScript::~CWaterScript()
{
}

void CWaterScript::Begin()
{
	Ptr<CFlipBook> pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\WaterBounce.flip");
	FlipBookComponent()->AddFlipBook(0, pFlipBook);
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\WaterExplosion.flip");
	FlipBookComponent()->AddFlipBook(1, pFlipBook);

	FlipBookComponent()->Play(0, 10, true);
}

void CWaterScript::Tick()
{
	CGameObject* pBoss = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Boss");
	Vec3 vBPos = pBoss->Transform()->GetRelativePos();
	Vec3 vPos = Transform()->GetRelativePos();

	m_Angle = atan2(vPos.y - vBPos.y, vPos.x - vBPos.x);

	m_XPos = (cos(m_Angle) * 100.f);
	m_YPos = (sin(m_Angle) * 100.f);

	Vec3 newPos = Vec3(m_XPos, m_YPos, 100.f);

	Transform()->SetRelativePos(newPos);

	m_Angle += DT;

	if (m_bShoot)
	{
		// m_dir 방향으로 직선 발사
	}
}

void CWaterScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider)
{
	if (_OtherObject->GetName() == L"Platform");
	{
		FlipBookComponent()->Play(1, 10, false);
		m_bShoot = false;
		if (FlipBookComponent()->IsFinish())
			DeleteObject(GetOwner());
	}
}

void CWaterScript::SaveToFile(FILE* _File)
{
}

void CWaterScript::LoadFromFile(FILE* _File)
{
}


