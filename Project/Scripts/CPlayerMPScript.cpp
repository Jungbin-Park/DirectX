#include "pch.h"
#include "CPlayerMPScript.h"

#include <Engine/CSprite.h>
#include <Engine/CLevel.h>
#include <Engine/CLevelMgr.h>
#include <Engine/CDevice.h>
#include <Engine/CConstBuffer.h>
#include <Engine/CGameObject.h>

#include "CPlayerScript.h"

CPlayerMPScript::CPlayerMPScript()
	: CScript(SCRIPT_TYPE::PLAYERMPSCRIPT)
	, m_MaxPlayerMP(1.f)
	, m_CurPlayerMP(1.f)
	, m_DamageHP(0.f)
{
}

CPlayerMPScript::~CPlayerMPScript()
{
}

void CPlayerMPScript::Begin()
{
}

void CPlayerMPScript::Tick()
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	CGameObject* Player = pCurLevel->FindObjectByName(L"Player");
	CPlayerScript* PlayerScript = nullptr;
	PlayerScript = (CPlayerScript*)Player->GetScriptByName(L"CPlayerScript");

	//m_FiveCount = PlayerScript->GetFiveDamageCount();
	//m_TenCount = PlayerScript->GetTenDamageCount();

	CConstBuffer* pCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::HUDMP);

	m_CurPlayerMP = PlayerScript->GetMP() / 100.f;

	tHUDMP tInfo = {};
	tInfo.MPRatio = m_CurPlayerMP;

	pCB->SetData(&tInfo);
	pCB->Binding();
}

void CPlayerMPScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider)
{
}

void CPlayerMPScript::SaveToFile(FILE* _File)
{
}

void CPlayerMPScript::LoadFromFile(FILE* _File)
{
}


