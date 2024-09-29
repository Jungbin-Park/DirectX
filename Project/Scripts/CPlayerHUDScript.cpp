#include "pch.h"
#include "CPlayerHUDScript.h"

#include <Engine/CSprite.h>
#include <Engine/CLevel.h>
#include <Engine/CLevelMgr.h>
#include <Engine/CDevice.h>
#include <Engine/CConstBuffer.h>
#include <Engine/CGameObject.h>

#include "CPlayerScript.h"

CPlayerHUDScript::CPlayerHUDScript()
	: CScript(SCRIPT_TYPE::PLAYERHUDSCRIPT)
	, m_MaxPlayerHP(1.f)
	, m_CurPlayerHP(1.f)
	, m_DamageHP(0.f)
{
}

CPlayerHUDScript::~CPlayerHUDScript()
{
}

void CPlayerHUDScript::Begin()
{
}

void CPlayerHUDScript::Tick()
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	CGameObject* Player = pCurLevel->FindObjectByName(L"Player");
	CPlayerScript* PlayerScript = nullptr;
	PlayerScript = (CPlayerScript*)Player->GetScriptByName(L"CPlayerScript");

	//m_FiveCount = PlayerScript->GetFiveDamageCount();
	//m_TenCount = PlayerScript->GetTenDamageCount();

	CConstBuffer* pCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::HUD);

	m_CurPlayerHP = PlayerScript->GetHP() / 100.f;

	tHUD tInfo = {};
	tInfo.HPRatio = m_CurPlayerHP;

	pCB->SetData(&tInfo);
	pCB->Binding();
}

void CPlayerHUDScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider)
{
}

void CPlayerHUDScript::SaveToFile(FILE* _File)
{
}

void CPlayerHUDScript::LoadFromFile(FILE* _File)
{
}


