#include "pch.h"
#include "CFireDragonScript.h"

#include <Engine/CLevel.h>
#include <Engine/CLevelMgr.h>

int CFireDragonScript::m_GlobalNum = 0;

CFireDragonScript::CFireDragonScript()
	: CScript(SCRIPT_TYPE::FIREDRAGONSCRIPT)
	, amplitude(2.0f)
	, frequency(0.03f)
	, speed(600.0f)
{
}

CFireDragonScript::~CFireDragonScript()
{
}

void CFireDragonScript::Begin()
{
	m_SparkPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\HitSpark.pref");
	m_Player = CLevelMgr::GetInst()->FindObjectByName(L"Player");

	Vec3 vPlayerPos = m_Player->Transform()->GetRelativePos();
	Vec3 vPos = Transform()->GetRelativePos();
	m_Dir = vPos - vPlayerPos;
	m_Dir.Normalize();

	Ptr<CFlipBook> pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\FireDragon.flip");
	FlipBookComponent()->AddFlipBook(0, pFlipBook);
	FlipBookComponent()->Play(0, 5, true);

	if (m_GlobalNum == 0)
	{
		m_GlobalNum++;
	}
	else
	{
		m_GlobalNum--;
	}
	m_Num = m_GlobalNum;
		
}

void CFireDragonScript::Tick()
{
	Vec3 vPos = Transform()->GetRelativePos();
	Vec3 prevPos = vPos;  // 이전 프레임의 위치
	Vec3 vRot = Transform()->GetRelativeRotation();

	vPos += speed * DT * m_Dir;  // 방향을 따라 이동

	float distance = (vPos - prevPos).Length();  // 이번 프레임의 이동 거리
	float offset = amplitude * sin(frequency * vPos.Length());  // 사인 곡선에 기반한 흔들림 계산

	// 드래곤의 이동 방향에 수직인 축에 사인 곡선 적용
	// 이동 방향에 수직한 축을 기준으로 y축이나 x축에 흔들림을 적용
	Vec3 perpendicularDir = Vec3(-m_Dir.y, m_Dir.x, 0.f);  // m_Dir에 수직인 방향 벡터
	vPos += perpendicularDir * offset;  // 수직 방향으로 흔들림 적용
	 

	//vPos.y += amplitude * sin(frequency * vPos.x);

	/*if (m_Num == 0)
		vPos.y += amplitude * sin(frequency * vPos.x);
	else
		vPos.y -= amplitude * sin(frequency * vPos.x);*/

	Transform()->SetRelativePos(vPos);

	// 이동 벡터 계산
	Vec3 direction = vPos - prevPos;
	direction.Normalize();  // 방향 벡터를 단위 벡터로 변환

	// 이동 방향에 따른 회전 각도 계산 (atan2를 사용하여 각도 구함)
	float angle = atan2(direction.y, direction.x);
	vRot.z = angle;
	// 오브젝트의 회전 값 설정
	Transform()->SetRelativeRotation(vRot);
}

void CFireDragonScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider)
{
	if (_OtherObject->GetName() == L"Platform");
	{
		Vec3 vPos = _OwnCollider->GetCollisionPoint();
		Instantiate(m_SparkPref, 0, vPos, L"HitSpark");
		DeleteObject(GetOwner());
	}
}

void CFireDragonScript::SaveToFile(FILE* _File)
{
}

void CFireDragonScript::LoadFromFile(FILE* _File)
{
}


