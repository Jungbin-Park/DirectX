#include "pch.h"
#include "CMAttackScript.h"

#include <Engine/CAssetMgr.h>
#include <Engine/assets.h>

CMAttackScript::CMAttackScript()
	:CScript(SCRIPT_TYPE::MATTACKSCRIPT)
{
}

CMAttackScript::~CMAttackScript()
{
}

void CMAttackScript::Begin()
{
	m_Age = 0.f;
	Collider2D()->SetActive(true);
}

void CMAttackScript::Tick()
{
	m_Age += DT;

	if (m_Age >= 0.1f)
	{
		DeleteObject(GetOwner());
	}
}

void CMAttackScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider)
{
	// 뒤로 밀어내기

	// 데미지 주기
}

void CMAttackScript::SaveToFile(FILE* _File)
{
}

void CMAttackScript::LoadFromFile(FILE* _File)
{
}


