#include "pch.h"
#include "CMAttackScript.h"

CMAttackScript::CMAttackScript()
	:CScript(SCRIPT_TYPE::MATTACKSCRIPT)
{
}

CMAttackScript::~CMAttackScript()
{
}

void CMAttackScript::Begin()
{
}

void CMAttackScript::Tick()
{
}

void CMAttackScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider)
{
	// �ڷ� �о��

	// ������ �ֱ�
}

void CMAttackScript::SaveToFile(FILE* _File)
{
}

void CMAttackScript::LoadFromFile(FILE* _File)
{
}

