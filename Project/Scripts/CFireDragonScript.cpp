#include "pch.h"
#include "CFireDragonScript.h"

CFireDragonScript::CFireDragonScript()
	: CScript(SCRIPT_TYPE::FIREDRAGONSCRIPT)
	, amplitude(50.0f)
	, frequency(0.03f)
	, speed(300.0f)
{
}

CFireDragonScript::~CFireDragonScript()
{
}

void CFireDragonScript::Begin()
{
	Ptr<CFlipBook> pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\FireDragon.flip");
	FlipBookComponent()->AddFlipBook(0, pFlipBook);
	FlipBookComponent()->Play(0, 5, true);
}

void CFireDragonScript::Tick()
{
	Vec3 vPos = Transform()->GetRelativePos();
	Vec3 prevPos = vPos;  // 이전 프레임의 위치
	vPos.x += speed * DT;
	vPos.y = amplitude * sin(frequency * vPos.x);

	Transform()->SetRelativePos(vPos);

	// 이동 벡터 계산
	Vec3 direction = vPos - prevPos;
	direction.Normalize();  // 방향 벡터를 단위 벡터로 변환

	// 이동 방향에 따른 회전 각도 계산 (atan2를 사용하여 각도 구함)
	float angle = atan2(direction.y, direction.x);

	// 오브젝트의 회전 값 설정
	Transform()->SetRelativeRotation(Vec3(0.f, 0.f, angle));
}

void CFireDragonScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider)
{
}

void CFireDragonScript::SaveToFile(FILE* _File)
{
}

void CFireDragonScript::LoadFromFile(FILE* _File)
{
}


