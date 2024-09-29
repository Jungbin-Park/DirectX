#include "pch.h"
#include "CBossHUDScript.h"

#include <Engine/CSprite.h>
#include <Engine/CLevel.h>
#include <Engine/CLevelMgr.h>
#include <Engine/CDevice.h>
#include <Engine/CConstBuffer.h>
#include <Engine/CGameObject.h>

#include "CBossScript.h"

CBossHUDScript::CBossHUDScript()
	: CScript(SCRIPT_TYPE::BOSSHUDSCRIPT)
	, m_MaxPlayerHP(1.f)
	, m_CurPlayerHP(1.f)
	, m_DamageHP(0.f)
{
}

CBossHUDScript::~CBossHUDScript()
{
}

void CBossHUDScript::Begin()
{
}

void CBossHUDScript::Tick()
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	CGameObject* Boss = pCurLevel->FindObjectByName(L"Boss");
	CBossScript* BossScript = nullptr;
	BossScript = (CBossScript*)Boss->GetScriptByName(L"CBossScript");

	//m_FiveCount = PlayerScript->GetFiveDamageCount();
	//m_TenCount = PlayerScript->GetTenDamageCount();

	CConstBuffer* pCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::BOSSHUD);

	m_CurPlayerHP = BossScript->GetHP() / 100.f;
	

	tHUD tInfo = {};
	tInfo.HPRatio = m_CurPlayerHP;

	pCB->SetData(&tInfo);
	pCB->Binding();
}

void CBossHUDScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider)
{
}

void CBossHUDScript::SaveToFile(FILE* _File)
{
}

void CBossHUDScript::LoadFromFile(FILE* _File)
{
}


