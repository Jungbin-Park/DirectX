#include "pch.h"
#include "CGhoulScript.h"

#include <Engine/CState.h>
#include <Engine/CFSM.h>
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

#include <States/CIdleState.h>
#include <States/CMoveState.h>
#include <States/CAttackState.h>
#include <States/CHitState.h>
#include <States/CDeadState.h>
#include <States/CStateMgr.h>

CGhoulScript::CGhoulScript()
	: CScript(SCRIPT_TYPE::GHOULSCRIPT)
	, m_Speed(300.f)
	, m_HP(100.f)
	, m_Cooldown(3.f)
	, m_DetectRange(500.f)
	, m_AttackRange(100.f)
{ 
}

CGhoulScript::~CGhoulScript()
{
}

void CGhoulScript::Begin()
{
	GetRenderComponent()->GetDynamicMaterial();

	FSM()->AddState(L"IdleState", new CIdleState);
	FSM()->AddState(L"MoveState", new CMoveState);
	FSM()->AddState(L"AttackState", new CAttackState);
	FSM()->AddState(L"HitState", new CHitState);
	FSM()->AddState(L"DeadState", new CDeadState);

	Ptr<CFlipBook> pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\GhoulIdleLeft.flip");
	FlipBookComponent()->AddFlipBook(0, pFlipBook);
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\GhoulIdleRight.flip");
	FlipBookComponent()->AddFlipBook(1, pFlipBook);
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\GhoulAttackLeft.flip");
	FlipBookComponent()->AddFlipBook(2, pFlipBook);
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\GhoulAttackRight.flip");
	FlipBookComponent()->AddFlipBook(3, pFlipBook);
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\GhoulMoveLeft.flip");
	FlipBookComponent()->AddFlipBook(4, pFlipBook);
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\GhoulMoveRight.flip");
	FlipBookComponent()->AddFlipBook(5, pFlipBook);
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\GhoulHitLeft.flip");
	FlipBookComponent()->AddFlipBook(6, pFlipBook);
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\GhoulHitRight.flip");
	FlipBookComponent()->AddFlipBook(7, pFlipBook);
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\GhouldDeadLeft.flip");
	FlipBookComponent()->AddFlipBook(8, pFlipBook);
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\GhouldDeadRight.flip");
	FlipBookComponent()->AddFlipBook(9, pFlipBook);

	FSM()->ChangeState(L"IdleState");

	m_Target = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Player");

}

void CGhoulScript::Tick()
{
	if (FSM()->GetCurState()->GetStateType() == STATE_TYPE::ATTACKSTATE)
	{
		if (FlipBookComponent()->IsFinish())
			FSM()->ChangeState(L"IdleState");
	}	
	
}

void CGhoulScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider)
{
	if (_OtherObject->GetLayerIdx() == 5)
	{
		FSM()->ChangeState(L"HitState");
	}
}

void CGhoulScript::SaveToFile(FILE* _File)
{
}

void CGhoulScript::LoadFromFile(FILE* _File)
{
}



