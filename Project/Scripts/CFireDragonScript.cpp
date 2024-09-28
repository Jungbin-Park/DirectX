#include "pch.h"
#include "CFireDragonScript.h"

CFireDragonScript::CFireDragonScript()
	: CScript(SCRIPT_TYPE::FIREDRAGONSCRIPT)
	, amplitude(200.0f)
	, frequency(0.5f)
	, speed(100.0f)
{
}

CFireDragonScript::~CFireDragonScript()
{
}

void CFireDragonScript::Begin()
{
}

void CFireDragonScript::Tick()
{
	Vec3 vPos = Transform()->GetRelativePos();
	Vec3 prevPos = vPos;  // ���� �������� ��ġ
	vPos.x += speed * DT;
	vPos.y = amplitude * sin(frequency * vPos.x);

	Transform()->SetRelativePos(vPos);

	// �̵� ���� ���
	Vec3 direction = vPos - prevPos;
	direction.Normalize();  // ���� ���͸� ���� ���ͷ� ��ȯ

	// �̵� ���⿡ ���� ȸ�� ���� ��� (atan2�� ����Ͽ� ���� ����)
	float angle = atan2(direction.y, direction.x);

	// ������Ʈ�� ȸ�� �� ����
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

