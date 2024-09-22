#include "pch.h"
#include "CManagerScript.h"

CManagerScript::CManagerScript()
	: CScript(SCRIPT_TYPE::MANAGERSCRIPT)
	, m_Score(0)
{
	SetName(L"ManagerScript");
}

CManagerScript::~CManagerScript()
{
}

void CManagerScript::Begin()
{
}

void CManagerScript::Tick()
{
	int a = 0;
}

void CManagerScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider)
{
}

void CManagerScript::SaveToFile(FILE* _File)
{
}

void CManagerScript::LoadFromFile(FILE* _File)
{
}


