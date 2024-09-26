#include "pch.h"
#include "CBSlashScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CTransform.h>

CBSlashScript::CBSlashScript()
	: CScript(SCRIPT_TYPE::BSLASHSCRIPT)
	, m_Boss(nullptr)
	, m_bSlash(false)
	, m_Speed(20.f)
	, m_Dir(Vec3(0.f, 0.f, 0.f))
	, m_Angle(0.f)
	, m_Dist(0.f)
	, m_StartAngle(0.f)
	, m_RotatedAngle(0.f)
{ 
}	  

CBSlashScript::~CBSlashScript()
{
}


void CBSlashScript::Begin()
{
	SetName(L"CBSlashScript");

	m_SparkPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\HitSpark.pref");

	Ptr<CFlipBook> pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\IceSwordSpawn.flip");
	FlipBookComponent()->AddFlipBook(0, pFlipBook);
	FlipBookComponent()->Play(0, 5, false);

	CGameObject* pBoss = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Boss");
	if (pBoss != nullptr)
		m_Boss = pBoss;

	Vec3 vBPos = m_Boss->Transform()->GetRelativePos();
	Vec3 vPos = Transform()->GetRelativePos();
	Vec3 vRelativePos = vPos - vBPos;

	m_Angle = atan2(vRelativePos.y, vRelativePos.x);
	m_Dist = sqrt(vRelativePos.x * vRelativePos.x + vRelativePos.y * vRelativePos.y);

	m_StartAngle = m_Angle;
	m_RotatedAngle = 0.0f;
	m_SlashCount = 2;
	m_CurSlashCount = 0;
}

void CBSlashScript::Tick()
{
	Vec3 vBPos = m_Boss->Transform()->GetRelativePos();
	Vec3 vPos = Transform()->GetRelativePos();

	Vec3 vStartDir = vPos - vBPos;
	vStartDir.Normalize();

	if (m_bSlash)
	{
		float previousAngle = m_Angle;
		m_Angle -= DT * m_Speed;

		float angleDelta = fabsf(m_Angle - previousAngle);
		m_RotatedAngle += angleDelta;

		float newX = vBPos.x + m_Dist * cosf(m_Angle);
		float newY = vBPos.y + m_Dist * sinf(m_Angle);

		GetOwner()->Transform()->SetRelativePos(Vec3(newX, newY, 0.f));
		GetOwner()->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, m_Angle - XM_PI / 2.f));

		
		if (m_RotatedAngle >= XM_2PI)
		{
			// 한 바퀴를 돌았을 때의 로직

			m_CurSlashCount++;
			m_RotatedAngle -= XM_2PI;

			if (m_CurSlashCount == m_SlashCount)
			{
				m_bSlash = false;
				DeleteObject(GetOwner());
			}
		}
	}
}

void CBSlashScript::Slash()
{
	m_bSlash = true;
}

void CBSlashScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider)
{
	if (_OtherObject->GetName() == L"Player")
	{
		Vec3 vPos = _OwnCollider->GetCollisionPoint();
		Instantiate(m_SparkPref, 0, vPos, L"HitSpark");
	}
}

void CBSlashScript::SaveToFile(FILE* _File)
{
}

void CBSlashScript::LoadFromFile(FILE* _File)
{
}



