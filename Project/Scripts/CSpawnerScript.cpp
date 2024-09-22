#include "pch.h"
#include "CSpawnerScript.h"

CSpawnerScript::CSpawnerScript()
	:CScript(SCRIPT_TYPE::SPAWNERSCRIPT)
{
}

CSpawnerScript::~CSpawnerScript()
{
}

void CSpawnerScript::Begin()
{
}

void CSpawnerScript::Tick()
{
}

void CSpawnerScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider)
{
}

void CSpawnerScript::SaveToFile(FILE* _File)
{
}

void CSpawnerScript::LoadFromFile(FILE* _File)
{
}



